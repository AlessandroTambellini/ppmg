#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
	{
		// Fill here your canvas.
		fill_triangle(pixels, WIDTH, HEIGHT, 
			(Point){WIDTH/20, HEIGHT/6},
			(Point){WIDTH/5, 20},
			(Point){WIDTH/5*2, HEIGHT/5*2}, GREEN);
		draw_line(pixels, WIDTH, HEIGHT, -WIDTH/4, HEIGHT/3*2, WIDTH/2, -HEIGHT/5, RED);
		fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, WIDTH/4, HEIGHT/4, HAZEL);
		fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4*3, HEIGHT/2, 100, FUCHSIA);
	}
	
	const char *filepath = "hello_ppmg.ppm";
	Errno err = save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
