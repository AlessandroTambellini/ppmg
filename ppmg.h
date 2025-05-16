#ifndef PPMG_H
#define PPMG_H

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BACKGROUND 0x1f1f1f
#define BLUE 0x1515c0
#define FUCHSIA 0xe500a5
#define GREEN 0x00e000
#define HAZEL 0x987b67
#define RED 0xda1010
#define SMOKE 0xd5d5d5
#define YELLOW 0xe5e500

typedef int Errno;
typedef uint32_t Color;

typedef struct Point {
	int x;
	int y;
} Point;

void fill_pixels(int pixels[], int width, int height, uint32_t color);
Errno save_to_ppm_file(int pixels[], int width, int height, const char *filepath);
void fill_rect(int *pixels, int img_width, int img_height, int x0, int y0, int rect_width, int rect_height, Color color);
void fill_circle(int *pixels, int img_width, int img_height, int cx, int cy, int r, Color color);
void draw_line(int *pixels, int img_width, int img_height, int x0, int y0, int x1, int y1, Color color);
void fill_triangle(int *pixels, int img_width, int img_height, Point p0, Point p1, Point p2, Color color);

#endif // PPMG_H
