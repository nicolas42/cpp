/*
usage
clang -Weverything mandelbrot.c ; ./a.out ; open out.ppm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct mandelbrot_t
{
    double x;
    double y;
    double zoom;
    int width;
    int height;
    int max_iterations;
    int padding;
} mandelbrot_t;

void draw_mandelbrot(mandelbrot_t arg);
void HSVtoRGB(int H, double S, double V, char output[3]);

void HSVtoRGB(int H, double S, double V, char output[3])
{
    // from https://gist.github.com/kuathadianto/200148f53616cbd226d993b400214a7f
    double C = S * V;
    double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    double m = V - C;
    double Rs, Gs, Bs;

    if (H >= 0 && H < 60)
    {
        Rs = C;
        Gs = X;
        Bs = 0;
    }
    else if (H >= 60 && H < 120)
    {
        Rs = X;
        Gs = C;
        Bs = 0;
    }
    else if (H >= 120 && H < 180)
    {
        Rs = 0;
        Gs = C;
        Bs = X;
    }
    else if (H >= 180 && H < 240)
    {
        Rs = 0;
        Gs = X;
        Bs = C;
    }
    else if (H >= 240 && H < 300)
    {
        Rs = X;
        Gs = 0;
        Bs = C;
    }
    else
    {
        Rs = C;
        Gs = 0;
        Bs = X;
    }

    output[0] = (char)((Rs + m) * 255);
    output[1] = (char)((Gs + m) * 255);
    output[2] = (char)((Bs + m) * 255);
}

void draw_mandelbrot(mandelbrot_t arg)
{
    double math_x = arg.x;
    double math_y = arg.y;
    double zoom = arg.zoom;

    // printf("%d %d %d\n", arg.width, arg.height, arg.max_iterations);

    // defaults
    int image_width = 500;
    int image_height = 500;
    int max_iterations = (int)(255 + (20 * log2(zoom)));

    // override if non-zero
    if (arg.width) image_width = arg.width;
    if (arg.height) image_height = arg.height;
    if (arg.max_iterations) max_iterations = arg.max_iterations;


    const unsigned char black[4] = {0, 0, 0, 255};
    // const unsigned char white[4] = {255, 255, 255, 255};

    // Open file and write header
    FILE *fp = fopen("out.ppm", "wb"); /* b - binary mode */
    (void)fprintf(fp, "P6 %d %d 255\n", image_width, image_height);

    // main loop
    for (int y = 0; y < image_height; y += 1)
    {
        for (int x = 0; x < image_width; x += 1)
        {

            double math_height = 4 / zoom;
            double math_width = 4 / zoom;

            // get math point from image point
            // image is flipped vertically. numbers go up, pixels go down. i don't care.
            double cx = (math_x - math_width / 2) + x * (math_width / image_width);
            double cy = (math_y - math_height / 2) + y * (math_width / image_width);
            double zx = 0;
            double zy = 0;

            int i;
            int in_set = 1;
            for (i = 1; i <= max_iterations; i += 1)
            {
                double zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                // if length of complex vector exceeds 4 then
                // assume the pixel is not in the set
                if (zx * zx + zy * zy > 4)
                {
                    in_set = 0;
                    break;
                }
            }

            if (in_set)
            {
                fwrite(black, 1, 3, fp);
                // printf("*");
            }
            else
            {
                char rgb[3];
                int hue = (int)((i % 255) / 255.0 * 360.0);
                HSVtoRGB(hue, 1, 0.5, rgb);
                fwrite(rgb, 1, 3, fp);
                // printf(" ");
            }
        }
    }
}

int main(void)
{

    mandelbrot_t places[13] = {
        {.x = -0.6999687500000003, .y = -0.2901249999999999, .zoom = 1024},
        {.x = -0.027285156250000026, .y = 0.6443066406250001, .zoom = 2048},
        {.x = -0.027120712995529206, .y = 0.6441158065199851, .zoom = 67108864},
        {.x = -0.027099643200635935, .y = 0.6440290103852749, .zoom = 268435456},
        {.x = -0.02709963878151032, .y = 0.6440290090395138, .zoom = 4294967296},
        {.x = 0.31923687500000003, .y = -0.4990148437499999, .zoom = 1024000},
        {.x = 0.31923733207893373, .y = -0.499014675590515, .zoom = 8388608000},
        {.x = 0.38715883591593053, .y = -0.25874134865963394, .zoom = 1073741824},
        {.x = 0.1347109374999998, .y = -0.6361328125, .zoom = 2048},
        {.x = 0.2681601562500003, .y = -0.004765624999999972, .zoom = 4096},
        {.x = 0.38715883594200756, .y = -0.2587413487062, .zoom = 536870912},
        {.x = 0.32898730468750015, .y = -0.4237490234374998, .zoom = 16384},
        {.x = -1.7664619022752155, .y = 0.041740019425749834, .zoom = 1073741824},
    };

    // printf("%f, %f, %f\n", places[0].x, places[0].y, places[0].zoom);

    draw_mandelbrot((mandelbrot_t){.x = -0.6999687500000003, .y = -0.2901249999999999, .zoom = 1024, .width = 2000, .height = 1000, .max_iterations = 1000});

    return 0;
}
