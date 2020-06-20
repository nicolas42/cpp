#ifndef MANDELBROT_H
#define MANDELBROT_H

// Draw a black and white mandelbrot image in file mandelbrot.ppm
// usage: mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int mandelbrot_simple(int pixel_width, int pixel_height, double xcenter, \
    double ycenter, double width, double height);

typedef struct {
    char* image;
    int pixel_width;
    int pixel_height;
    double xcenter;
    double ycenter;
    double width;
    double height;
    size_t size;
} mandelbrot_t;

void* mandelbrot(void* arg);
void mandelbrot_usage(void);
int mandelbrot_main(int argc, char** argv);

#endif


void* mandelbrot( void* arg)
{

    mandelbrot_t a = *(mandelbrot_t*) arg;

    int pixel_width = a.pixel_width;
    int pixel_height = a.pixel_height;
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
    const double width_per_pixel = (xmax - xmin) / pixel_width;
    const double height_per_pixel = (ymax - ymin) / pixel_height;
    
    for (int y = 0; y < pixel_height ; y += 1) {
        for (int x = 0; x < pixel_width; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride;
            double i, imax;

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
				a.image[y*pixel_width*3 + x*3 + 0] = white[0] * (char)(i / imax);
                a.image[y*pixel_width*3 + x*3 + 1] = white[1] * (char)(i / imax);
                a.image[y*pixel_width*3 + x*3 + 2] = white[2] * (char)(i / imax);

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

void mandelbrot_usage(void){
	printf("mandelbrot [pixel_width] [pixel_height]\r\n");
}

int mandelbrot_main(int argc, char** argv){

    int arg_shift = 1;
    // the usage went from 
    // mandelbrot [arguments]
    // generic-binary mandelbrot [arguments]
    // so all the argument indeces went up by one

    int pixel_width, pixel_height;
    double xcenter, ycenter, width, height;

    pixel_width = 1000; pixel_height = 1000;
    xcenter = 0; ycenter = 0; width = 4; height = 4;

    char* ptr;

    switch ( argc - arg_shift ){
	case 1:
		mandelbrot_usage(); 
        printf("Making 1000x1000 mandelbrot image...\r\n");
		break;
	case 3:
		pixel_width = atoi(argv[ 1 + arg_shift ]); 
		pixel_height = atoi(argv[ 2 + arg_shift ]);
        printf("Making %dx%d mandelbrot image...\r\n", pixel_width, pixel_height);		
		break;
	case 6:
		pixel_width = atoi(argv[ 1 + arg_shift ]); 
		pixel_height = atoi(argv[ 2 + arg_shift ]);
		xcenter = strtod(argv[ 3 + arg_shift ], &ptr);
		ycenter = strtod(argv[ 4 + arg_shift ], &ptr);
		width = strtod(argv[ 5 + arg_shift ], &ptr);
		height = strtod(argv[ 5 + arg_shift ], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	case 7:
		pixel_width = atoi(argv[ 1 + arg_shift ]); 
		pixel_height = atoi(argv[ 2 + arg_shift ]);
		xcenter = strtod(argv[ 3 + arg_shift ], &ptr);
		ycenter = strtod(argv[ 4 + arg_shift ], &ptr);
		width = strtod(argv[ 5 + arg_shift ], &ptr);
		height = strtod(argv[ 6 + arg_shift ], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	default:
		mandelbrot_usage(); 
		return 1;
	}

   double t1, t2; 
    t1 = clock()/(double)CLOCKS_PER_SEC;


    mandelbrot_t a;

    a.pixel_width = pixel_width;
    a.pixel_height = pixel_height;
    a.xcenter = xcenter;
    a.ycenter = ycenter;
    a.width = width;
    a.height = height;
    a.size = (size_t)(pixel_height * pixel_width) * 3 * sizeof(char);
    a.image = (char*)malloc(a.size);
    
    mandelbrot(&a);


    // Open file and write header
	char* filename = "mandelbrot.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    for (size_t i = 0; i < a.size; i++){
        fputc(a.image[i], fp);
    }
    
    (void) fclose(fp);

    t2 = clock()/(double)CLOCKS_PER_SEC;
    printf("time: %.3f\n", t2-t1);

    
    return 0;
}

int mandelbrot_simple(int pixel_width, int pixel_height, double xcenter, \
    double ycenter, double width, double height)
{

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
    
    // Open file and write header
	char* filename = "mandelbrot.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    for (int y = 0; y < pixel_height; y += 1) {
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
				fwrite(black, 1, 3, fp);
				// printf("*");
            } else {
				fputc(white[0] * i / imax, fp);
				fputc(white[1] * i / imax, fp);
				fputc(white[2] * i / imax, fp);
				// printf(" ");
			}
        }
		// printf("\n");
    }

  (void) fclose(fp);
  return 0;
}
