#include "../ppmg.h"

#define WIDTH  800
#define HEIGHT 600

uint32_t pixels[WIDTH*HEIGHT];

int main(void)
{
    fill_pixels(pixels, WIDTH, HEIGHT, 0xff1f1f1f);

    /* top-left */ fill_rect(pixels, WIDTH, HEIGHT, -WIDTH/2, -HEIGHT/2, WIDTH-10, HEIGHT-10, RED);
    /* top-right */ fill_rect(pixels, WIDTH, HEIGHT, WIDTH-20, 20, (-WIDTH/2)+30, HEIGHT/2-30, SMOKE);
    /* bottom-right */ fill_rect(pixels, WIDTH, HEIGHT, WIDTH*3/2, HEIGHT*3/2, -WIDTH+10, -HEIGHT+10, GREEN);
    /* bottom-left */ fill_rect(pixels, WIDTH, HEIGHT, 20, HEIGHT-20, WIDTH/2-30, -HEIGHT/2+30, YELLOW);
    
    const char *filepath = "rectangles.ppm";
    Errno err = save_to_ppm_file(pixels, WIDTH, HEIGHT, filepath);
    if (err) {
        fprintf(stderr, "Error: Couldn't save file '%s': %s\n", filepath,                strerror(errno));
        return 1;
    }

    return 0;
}

