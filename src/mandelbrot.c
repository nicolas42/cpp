#include "mandelbrot.h"

int mandelbrot(int pixel_width, int pixel_height, double xcenter, \
    double ycenter, double width, double height, char* filename)
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
	// char* filename = "mandelbrot.ppm";
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

void mandelbrot_usage(void){
	printf("mandelbrot [pixel_width] [pixel_height]\r\n");
}

int mandelbrot_main(int argc, char** argv){

    int pixel_width, pixel_height;
    double xcenter, ycenter, width, height;

    pixel_width = 1000; pixel_height = 1000;
    xcenter = 0; ycenter = 0; width = 4; height = 4;

    char* ptr;

    switch (argc){
	case 1:
		mandelbrot_usage(); 
        printf("Making 1000x1000 mandelbrot image...\r\n");
		break;
	case 3:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
        printf("Making %dx%d mandelbrot image...\r\n", pixel_width, pixel_height);		
		break;
	case 6:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
		xcenter = strtod(argv[3], &ptr);
		ycenter = strtod(argv[4], &ptr);
		width = strtod(argv[5], &ptr);
		height = strtod(argv[5], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	case 7:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
		xcenter = strtod(argv[3], &ptr);
		ycenter = strtod(argv[4], &ptr);
		width = strtod(argv[5], &ptr);
		height = strtod(argv[6], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	default:
		mandelbrot_usage(); 
		return 1;
	}
    // printf("\nargc: %d\n", argc);
    mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height, "out.ppm");
    
    return 0;
}

