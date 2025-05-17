#include "ppmg.h"

// Using '(value)' instead of 'value' is considered a safeguard for whatever
// reason.
#define return_defer(value) \
	do { res = (value); goto defer; } while (0)

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void ppmg_fill_pixels(int pixels[], int width, int height, uint32_t color) {
	for (int i = 0; i < height*width; i++) {
		pixels[i] = color;
	} 
}

Errno ppmg_save_to_ppm_file(int pixels[], int width, int height, const char *filepath) 
{
	int res = 0;
	FILE *f = fopen(filepath, "w");

	{
		if (!f)	return_defer(errno);

		fprintf(f, "P3\n%d %d 255\n", width, height);
		if (ferror(f)) return_defer(errno);

		for (int i = 0; i < width*height; i++) 
		{
			uint32_t pixel = pixels[i];
			uint8_t r = (pixel >> (8*2)) & 0xff;
			uint8_t g =	(pixel >> (8*1)) & 0xff;
			uint8_t b = (pixel >> (8*0)) & 0xff;

			fprintf(f, "%d %d %d\n", r, g, b);
			if (ferror(f)) return_defer(errno);
		}
	}

defer:
	if (f) fclose(f);
	return res;
}

void ppmg_fill_rect(int *pixels, int img_width, int img_height, int x0, int y0, int rect_width, int rect_height, Color color)
{
	if (rect_width < 0) {
		rect_width = -rect_width;
		x0 = x0 - rect_width;
	}

	if (rect_height < 0) {
		rect_height = -rect_height;
		y0 = y0 - rect_height;
	}

	for (int y = y0; y < y0 + rect_height; y++) {
		if (0 <= y && y < img_height) {
			for (int x = x0; x < x0 + rect_width; x++) {
				if (0 <= x && x < img_width) {
					pixels[img_width*y + x] = color;
				}
			}
		}
	}
}

void ppmg_fill_circle(int *pixels, int img_width, int img_height, int cx, int cy, int r, Color color) 
{
	if (r < 0) r = -r;

	int xl = cx - r; // left
	int xr = cx + r; // right
	int yt = cy - r; // top
	int yb = cy + r; // bottom

	for (int y = yt; y <= yb; y++) {
		// Vertical boundaries
		if (0 <= y && y < img_height) {
			for (int x = xl; x <= xr; x++) {
				// Horizontal boundaries
				if (0 <= x && x < img_width) {
					int dx = x-cx;
					int dy = y-cy;
					// sqrt(dx*dx + dy*dy) <= r
					if (dx*dx + dy*dy <= r*r) {
						pixels[y*img_width + x] = color;
					}
				}
			}
		}
	}
}

void ppmg_draw_line(int *pixels, int img_width, int img_height, int x0, int y0, int x1, int y1, Color color)
{
	if (x1 < x0) {
		swap(&x0, &x1);
		// If the x is swapped, also the y has to be swapped, because they are
		// part of the same point.
		swap(&y0, &y1);
	}

	// y = mx + q, where m = (y1 - y0)/(x1 - x0)

	if (x1 == x0) {
		// Vertical Line, m -> Infinity
		int x = x0;
		for (int y = y0; y <= y1; y++) {
			if (0 <= y && y < img_height) {
				pixels[y*img_width + x] = color;	
			}
		}
	} 
	else {
		float m = (float)(y1 - y0) / (x1 - x0); 
		float q = (float)y0 - m*x0;

		for (int x = x0; x <= x1; x++) {
			if (0 <= x && x < img_width) {
				int y = (int)(m*x + q);
				if (0 <= y && y < img_height) {
					pixels[y*img_width + x] = color;	
					if (y < img_height-1) {
						int next_y = (int)(m*(x+1)+q);
						// dy: delta y; fill the vertical gaps between an x and the next
						// one.
						for (int dy = y+1; dy < next_y; dy++) {
							if (dy < img_height) pixels[dy*img_width + x] = color;	
						}
					}
				}
			}
		}
	}
}

// With three points, when calling the function, I felt was handier to pass a
// Point data-structure instead of passing the single coordinates separately. So, this
// function, contraty to the other ones, uses a Point ds.
void ppmg_fill_triangle(int *pixels, int img_width, int img_height, Point p0, Point p1, Point p2, Color color) 
{
	// Sort the points by y: y0 <-> y1 <-> y2
	if (p0.y > p1.y) {
		swap(&p0.x, &p1.x);
		swap(&p0.y, &p1.y);
	}

	if (p1.y > p2.y) {
		swap(&p1.x, &p2.x);
		swap(&p1.y, &p2.y);
	}

	if (p0.y > p1.y) {
		swap(&p0.x, &p1.x);
		swap(&p0.y, &p1.y);
	}

	int dy_p0p1 = p1.y - p0.y;
	int dx_p0p1 = p1.x - p0.x;

	int dy_p0p2 = p2.y - p0.y;
	int dx_p0p2 = p2.x - p0.x;

	// Top-half of the triangle
	for (int y = p0.y; 0 <= y && y <= p1.y && y < img_height; y++) 
	{
		// For each r: y = k (costant), get the points x0 and x1 where r 
		// intersects the straight lines p0p1 and p0p2.
	
		// m = (dy_p0p1/dx_p0p1)
		// q = p0.y - (dy_p0p1/dx_p0p1)*p0.x
		// x = (y - q)*(dx_p0p1/dy_p0p1)
		//   = (y - p0.y + (dy_p0p1/dx_p0p1)*p0.x)*(dx_p0p1/dy_p0p1)
		//   = (y - p0.y)*(dx_p0p1/dy_p0p1) + p0.x

		int x01 = dy_p0p1 != 0 ? (y - p0.y)*((float)dx_p0p1/dy_p0p1) + p0.x : p0.x;
		int x02 = dy_p0p2 != 0 ? (y - p0.y)*((float)dx_p0p2/dy_p0p2) + p0.x : p0.x;
		if (x01 > x02) swap(&x01, &x02);

		for (int x = x01; 0 <= x && x <= x02 && x < img_width; x++)
		{
			pixels[y*img_width + x] = color;
		}
	}

	int dy_p2p1 = p2.y - p1.y;
	int dx_p2p1 = p2.x - p1.x;
	
	int dy_p2p0 = p2.y - p0.y;
	int dx_p2p0 = p2.x - p0.x;
	
	// Bottom-half of the triangle (the y grows from top to bottom of the
	// canvas)
	for (int y = p1.y; 0 <= y && y <= p2.y && y < img_height; y++)
	{
		int x12 = dy_p2p1 != 0 ? (y - p2.y)*((float)dx_p2p1/dy_p2p1) + p2.x : p2.x;
		int x20 = dy_p2p0 != 0 ? (y - p2.y)*((float)dx_p2p0/dy_p2p0) + p2.x : p2.x;
		if (x12 > x20) swap(&x12, &x20);

		for (int x = x12; 0 <= x && x <= x20 && x < img_width; x++) {
			pixels[y*img_width + x] = color;
		}
	}
}

