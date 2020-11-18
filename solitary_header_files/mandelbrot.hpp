#ifndef MANDELBROT_H
#define MANDELBROT_H

// typedef struct box {
//     double x = 0;
//     double y = 0;
//     double w = 1;
//     double h = 1;
// } box;


typedef struct image {
    int w;
    int h;
    int c;
    char* data;
} image;

image make_image(int w, int h, int c)
{
    image im;
    im.w=w; 
    im.h=h; 
    im.c=c; 
    im.data = (char*)malloc(w*h*c*sizeof(char));
    return im;
}

void free_image(image im)
{
    free(im.data);
}


image draw_mandelbrot( int image_width = 800, int image_height = 800, int image_channels = 3, double x = 0, double y = 0, double w = 4, double h = 4 )
{
    image im = make_image(image_width, image_height, image_channels);

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};
    
    for (int j = 0; j < im.h ; j += 1) 
    {
        for (int i = 0; i < im.w; i += 1) 
        {
            const int max_iterations = 40;

            double zx, zxtmp, zy, cx, cy;
            cx = i * w/im.w + x - w/2;
            cy = j * h/im.h + y - h/2;
            zx = 0;
            zy = 0;

            int is_in_set = 1, iter;
            for(iter = 1; iter <= max_iterations; iter += 1)
            {
                // z1 = z0^2 + c
                // z = a+bj, c = c+dj
                // z^2 = (a+bj)(a+bj) = a^2 - b^2 + 2abj
                // horizontal coordinate is a^2-b^2 + c
                // vertical coordinate is 2ab + d

                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                // if the radius is greater than 2 then assume divergence
                if(zx * zx + zy * zy > 4)
                {
                    is_in_set = 0;
                    break;
                }
            }
            
            if (is_in_set) 
            {
				im.data[j*im.w*im.c + i*im.c + 0] = (char)black[0];
                im.data[j*im.w*im.c + i*im.c + 1] = (char)black[1];
                im.data[j*im.w*im.c + i*im.c + 2] = (char)black[2];
            } 
            else 
            {
				im.data[j*im.w*im.c + i*im.c + 0] = white[0] * iter / max_iterations;
                im.data[j*im.w*im.c + i*im.c + 1] = white[1] * iter / max_iterations;
                im.data[j*im.w*im.c + i*im.c + 2] = white[2] * iter / max_iterations;
			}
        }
    }
    return im;
}


int demo_draw_mandelbrot(int imw=800, int imh=800, int imc=3, double x=0.2, double y=0.2, double w=2, double h=2)
{
    image im = draw_mandelbrot( imw, imh, imc, x, y, w, h );

    // Write PPM File
	const char* filename = "out.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", im.w, im.h);
    for (size_t i = 0; i < im.c * im.h * im.w; i++){
        fputc(im.data[i], fp);
    }
    (void) fclose(fp);

    free_image(im);
    return 0;
}


#endif
