#include "ppmg.h"

#define WIDTH 800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
    ppmg_fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
    {
        // Fill here the canvas.
    }

    const char *filename = "image.ppm";
    Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filename);
    if (err) {
        fprintf(stderr, "Error while saving the file '%s'.\n", filename);
    }

    return 0;
}
