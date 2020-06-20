#ifndef MANDELBROT_H
#define MANDELBROT_H

// Draw a black and white mandelbrot image in file mandelbrot.ppm
// usage: mandelbrot(w, h, xcenter, ycenter, width, height);

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    char* image;
    int w;
    int h;
    int c;
    double xcenter;
    double ycenter;
    double width;
    double height;
} mandelbrot_arg;

void* mandelbrot(void* arg);
void mandelbrot_usage(void);
int mandelbrot_main(int argc, char** argv);

void* mandelbrot( void* arg)
{

    mandelbrot_arg a = *(mandelbrot_arg*) arg;

    int w = a.w;
    int h = a.h;
    int c = a.c;
    double xcenter = a.xcenter;
    double ycenter = a.ycenter;
    double width = a.width;
    double height = a.height;

    // to see full image: mandelbrot(1000,1000,0,0,4,4);

    // center, width
    // double xcenter,ycenter, width, height;
    double xmin, xmax, ymin, ymax;

    // xcenter = 0; ycenter = 0; width = 4; height = 4;
    xmin = xcenter - width/2;
    xmax = xcenter + width/2;
    ymin = ycenter - height/2;
    ymax = ycenter + height/2;

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};

    // length per pixel
    const double width_per_pixel = (xmax - xmin) / w;
    const double height_per_pixel = (ymax - ymin) / h;
    
    for (int y = 0; y < h ; y += 1) {
        for (int x = 0; x < w; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride, i, imax;

            // stride = 3;
            imax = 40;

            // image is flipped vertically
            cx = x * width_per_pixel - xmax;
            cy = y * height_per_pixel - ymax;
            zx = 0;
            zy = 0;
            is_in_set = 1;

            for(i = 1; i <= imax; i += 1){
                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                if(zx * zx + zy * zy > 4){
                    is_in_set = 0;
                    break;
                }
            }
            
            if (is_in_set) {
				a.image[y*w*c + x*c + 0] = (char)black[0];
                a.image[y*w*c + x*c + 1] = (char)black[1];
                a.image[y*w*c + x*c + 2] = (char)black[2];

				// fputc(black[0], fp);
				// fputc(black[1], fp);
				// fputc(black[2], fp);
				// printf("*");
            } else {
				a.image[y*w*c + x*c + 0] = white[0] * i / imax;
                a.image[y*w*c + x*c + 1] = white[1] * i / imax;
                a.image[y*w*c + x*c + 2] = white[2] * i / imax;

				// fputc(white[0] * i / imax, fp);
				// fputc(white[1] * i / imax, fp);
				// fputc(white[2] * i / imax, fp);
				// printf(" ");
			}
        }
		// printf("\n");
    }
    return (void*)0;
}

int main(int argc, char** argv){

    double t1, t2; 
    t1 = clock()/(double)CLOCKS_PER_SEC;

    // Make Mandelbrot Image
    mandelbrot_arg a;
    a.w = 1000;
    a.h = 1000;
    a.c = 3;
    a.xcenter = 0;
    a.ycenter = 0;
    a.width = 4;
    a.height = 4;
    a.image = malloc(a.c * a.h * a.w * sizeof(char));
    mandelbrot(&a);


    // Write File
	char* filename = "out.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", a.w, a.h);
    for (size_t i = 0; i < a.c * a.h * a.w; i++){
        fputc(a.image[i], fp);
    }
    (void) fclose(fp);


    // Print Duration
    t2 = clock()/(double)CLOCKS_PER_SEC;
    printf("time: %.3f\n", t2-t1);

    return 0;
}

#endif

