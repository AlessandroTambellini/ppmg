#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
	
	fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2,  WIDTH/2, -HEIGHT/2, SMOKE);
	fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2,  WIDTH/2,  HEIGHT/2, GREEN);
	fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, -WIDTH/2,  HEIGHT/2, YELLOW);
	fill_rect(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, -WIDTH/2, -HEIGHT/2, RED);
	
	fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4,   HEIGHT/2, WIDTH/8, BLUE);	
	fill_circle(pixels, WIDTH, HEIGHT, WIDTH/4*3, HEIGHT/2, WIDTH/8, FUCHSIA);	
	
	const char *filepath = "colors.ppm";
	Errno err = save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
