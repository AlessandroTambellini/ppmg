#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{	
	fill_pixels(pixels, WIDTH, HEIGHT, 0xff1f1f1f);

	int r = 50;
	int d = 2*r;
	int rows = HEIGHT/d;
	int cols = WIDTH/d;
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			int cy = j*d + r;
			int cx = i*d + r;
			fill_circle(pixels, WIDTH, HEIGHT, cx, cy, r, 0xff0000);
		}
	}
	
	const char *filepath = "circles_grid.ppm";
	Errno err = save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
