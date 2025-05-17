#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	ppmg_fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
	
	ppmg_fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2,  WIDTH/2, -HEIGHT/2, SMOKE);
	ppmg_fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2,  WIDTH/2,  HEIGHT/2, GREEN);
	ppmg_fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, -WIDTH/2,  HEIGHT/2, YELLOW);
	ppmg_fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, -WIDTH/2, -HEIGHT/2, RED);
	
	ppmg_fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4,   HEIGHT/2, WIDTH/8, BLUE);	
	ppmg_fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4*3, HEIGHT/2, WIDTH/8, FUCHSIA);	
	
	const char *filepath = "colors.ppm";
	Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
