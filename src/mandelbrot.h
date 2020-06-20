#ifndef MANDELBROT_H
#define MANDELBROT_H

// Draw a black and white mandelbrot image in file mandelbrot.ppm
// usage: mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);

#include <stdio.h>
#include <stdlib.h>

int mandelbrot(int pixel_width, int pixel_height, double xcenter, \
    double ycenter, double width, double height, char* filename);
void mandelbrot_usage(void);
int mandelbrot_main(int argc, char** argv);

#endif
