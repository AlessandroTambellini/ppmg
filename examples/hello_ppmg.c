#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	ppmg_fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
	{
		// Fill here your canvas.
		ppmg_fill_triangle(pixels, WIDTH, HEIGHT, 
			(Point){WIDTH/20, HEIGHT/6},
			(Point){WIDTH/5, 20},
			(Point){WIDTH/5*2, HEIGHT/5*2}, GREEN);
		ppmg_draw_line(pixels, WIDTH, HEIGHT, -WIDTH/4, HEIGHT/3*2, WIDTH/2, -HEIGHT/5, RED);
		ppmg_fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, WIDTH/4, HEIGHT/4, HAZEL);
		ppmg_fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4*3, HEIGHT/2, 100, FUCHSIA);
	}
	
	const char *filepath = "hello_ppmg.ppm";
	Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
