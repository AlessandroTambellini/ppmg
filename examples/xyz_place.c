#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
	ppmg_fill_pixels(pixels, WIDTH, HEIGHT, 0xff1f1f1f);
	
	/* y-Axis              */ ppmg_draw_line(pixels, WIDTH, HEIGHT, WIDTH/2, 0, WIDTH/2, HEIGHT, GREEN);
	/* yellow-horiz-behind */ ppmg_draw_line(pixels, WIDTH, HEIGHT, WIDTH/10*3, HEIGHT/10*4, WIDTH, HEIGHT/10*4, YELLOW);
	/* x-Axis              */ ppmg_draw_line(pixels, WIDTH, HEIGHT, WIDTH/10, HEIGHT/2, WIDTH/10*9, HEIGHT/2, GREEN);
	/* yellow-horiz-front  */ ppmg_draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/10*6, WIDTH/10*7, HEIGHT/10*6, YELLOW);
	/* yellow-left         */ ppmg_draw_line(pixels, WIDTH, HEIGHT, 0, HEIGHT/10*6, WIDTH/10*3, HEIGHT/10*4, YELLOW);
	/* yellow-right        */ ppmg_draw_line(pixels, WIDTH, HEIGHT, WIDTH/10*7, HEIGHT/10*6, WIDTH, HEIGHT/10*4, YELLOW);
	/* red                 */ ppmg_draw_line(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, WIDTH/10*7, HEIGHT/10*1, RED);

	const char *filepath = "xyz_place.ppm";
	Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
