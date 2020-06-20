#ifndef MANDELBROT_H
#define MANDELBROT_H

// Draw a black and white mandelbrot image in file mandelbrot.ppm
// usage: mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    size_t image_index;
    char* image;
    int pixel_width;
    int pixel_height;
    double xcenter;
    double ycenter;
    double width;
    double height;
    int ystart;
    int yend;
} mandelbrot_arg;

void* mandelbrot(void* arg);
void mandelbrot_usage(void);
int mandelbrot_main(int argc, char** argv);



void* mandelbrot( void* arg)
{

    mandelbrot_arg a = *(mandelbrot_arg*) arg;

    int pixel_width = a.pixel_width;
    int pixel_height = a.pixel_height;
    double xcenter = a.xcenter;
    double ycenter = a.ycenter;
    double width = a.width;
    double height = a.height;
    int ystart = a.ystart;
    int yend = a.yend;

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
    const double width_per_pixel = (xmax - xmin) / pixel_width;
    const double height_per_pixel = (ymax - ymin) / pixel_height;
    
    for (int y = ystart; y <= yend ; y += 1) {
        for (int x = 0; x < pixel_width; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride, i, imax;

            stride = 3;
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
				a.image[y*pixel_width*3 + x*3 + 0] = (char)black[0];
                a.image[y*pixel_width*3 + x*3 + 1] = (char)black[1];
                a.image[y*pixel_width*3 + x*3 + 2] = (char)black[2];

				// fputc(black[0], fp);
				// fputc(black[1], fp);
				// fputc(black[2], fp);
				// printf("*");
            } else {
				a.image[y*pixel_width*3 + x*3 + 0] = white[0] * i / imax;
                a.image[y*pixel_width*3 + x*3 + 1] = white[1] * i / imax;
                a.image[y*pixel_width*3 + x*3 + 2] = white[2] * i / imax;

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

    int pixel_width, pixel_height;
    double xcenter, ycenter, width, height;

    pixel_width = 1000; pixel_height = 1000;
    xcenter = 0; ycenter = 0; width = 4; height = 4;

    mandelbrot_arg a;

    a.image = malloc(3*1000*1000 * sizeof(char));
    a.pixel_width = pixel_width;
    a.pixel_height = pixel_height;
    a.xcenter = xcenter;
    a.ycenter = ycenter;
    a.width = width;
    a.height = height;
    a.ystart = 0;
    a.yend = pixel_height;
    
    // mandelbrot(&a);


    // // Open file and write header
	// char* filename = "mandelbrot.ppm";
	// FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	// (void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    // for (size_t i = 0; i < 3e6; i++){
    //     fputc(a.image[i], fp);
    // }
    
    // (void) fclose(fp);

    #define num_threads 1000
	mandelbrot_arg targs[num_threads];
	pthread_t tids[num_threads];

	for (int i = 0; i < num_threads; i++) {

		targs[i] = a;
        targs[i].ystart = i;
        targs[i].yend = i;

		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tids[i], &attr, mandelbrot, &targs[i]);
	}

	// Wait for threads
	for (size_t i = 0; i < num_threads; i++) {
    // for (int i = num_threads-1; i >= 0 ; i -= 1 ){
		pthread_join(tids[i], NULL);
        // printf("time: %.3f ", get_time() - t1 );        
	}



    // Open file and write header
	char* filename = "mandelbrot.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    for (size_t i = 0; i < 3*1000*1000; i++){
        fputc(a.image[i], fp);
    }
    
    (void) fclose(fp);

    t2 = clock()/(double)CLOCKS_PER_SEC;
    printf("time: %.3f\n", t2-t1);



    return 0;
}


#endif

