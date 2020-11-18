/*
g++ -std=c++11 main.cpp; ./out
*/

#include <iostream>
#include "sha1.hpp"
// #include "opencv_demos.hpp"
// to include opencv libraries in unix use `pkg-config --cflags --libs opencv4`

#include "mandelbrot.hpp"
#include "multivector.hpp"

int main()
{
/*
    std::string sha1_hash = sha1::sha1("Hello World!\n");
    std::cout << sha1_hash << std::endl;
    
    multivector::main();
*/

    int w=800; int h=800; int c=3;
    image im = draw_mandelbrot( w, h, c, 0,0,4,4 );

    image red_channel   = make_image(w,h,1);
    image green_channel = make_image(w,h,1);
    image blue_channel  = make_image(w,h,1);
    for ( size_t i = 0; i < im.h * im.w; i += 3 )
    {
        red_channel.data[i]   = im.data[i];
        green_channel.data[i] = im.data[i+1];
        blue_channel.data[i]  = im.data[i+2];
    }

    return 0;
}
