#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

uint32_t pixels[WIDTH*HEIGHT];

int main(void) 
{	
	ppmg_fill_pixels(pixels, WIDTH, HEIGHT, 0xff1f1f1f);

	int rect_dim = 100;
	int rows = HEIGHT/rect_dim;
	int cols = WIDTH/rect_dim;
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			if ((i+j) % 2 == 0) {
				ppmg_fill_rect(pixels, WIDTH, HEIGHT, rect_dim*i, rect_dim*j, rect_dim, rect_dim, RED);
			}
		}
	}

	const char *filepath = "rectangles_grid.ppm";
	Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
	if (err) {
		fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath, strerror(errno));
		return 1;
	}

	return 0;
}
