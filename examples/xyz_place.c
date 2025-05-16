#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	fill_pixels(pixels, WIDTH, HEIGHT, 0xff1f1f1f);
	
	/* y-Axis              */ draw_line(pixels, WIDTH, HEIGHT, WIDTH/2, 0, WIDTH/2, HEIGHT, GREEN);
	/* yellow-horiz-behind */ draw_line(pixels, WIDTH, HEIGHT, WIDTH/10*3, HEIGHT/10*4, WIDTH, HEIGHT/10*4, YELLOW);
	/* x-Axis              */ draw_line(pixels, WIDTH, HEIGHT, WIDTH/10, HEIGHT/2, WIDTH/10*9, HEIGHT/2, GREEN);
	/* yellow-horiz-front  */ draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/10*6, WIDTH/10*7, HEIGHT/10*6, YELLOW);
	/* yellow-left         */ draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/10*6, WIDTH/10*3, HEIGHT/10*4, YELLOW);
	/* yellow-right        */ draw_line(pixels, WIDTH, HEIGHT, WIDTH/10*7, HEIGHT/10*6, WIDTH, HEIGHT/10*4, YELLOW);
	/* red                 */ draw_line(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, WIDTH/10*7, HEIGHT/10*1, RED);

	const char *filepath = "xyz_place.ppm";
	Errno err = save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
