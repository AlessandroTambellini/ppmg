#ifndef PPMG_H
#define PPMG_H

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BACKGROUND 0x1f1f1fff
#define BLUE 0x1515c0ff
#define FUCHSIA 0xe500a5ff
#define GREEN 0x00e000ff
#define HAZEL 0x987b67ff
#define RED 0xda1010ff
#define SMOKE 0xd5d5d5ff
#define YELLOW 0xe5e500ff

typedef int Errno;
typedef uint32_t Color;

typedef struct Point {
	int x;
	int y;
} Point;

void ppmg_fill_pixels(int pixels[], int width, int height, uint32_t color);
Errno ppmg_save_to_ppm_file(int pixels[], int width, int height, const char *filepath);
void ppmg_fill_rect(int *pixels, int img_width, int img_height, int x0, int y0, int rect_width, int rect_height, Color color);
void ppmg_fill_circle(int *pixels, int img_width, int img_height, int cx, int cy, int r, Color color);
void ppmg_draw_line(int *pixels, int img_width, int img_height, int x0, int y0, int x1, int y1, Color color);
void ppmg_fill_triangle(int *pixels, int img_width, int img_height, Point p0, Point p1, Point p2, Color color);

#endif // PPMG_H
