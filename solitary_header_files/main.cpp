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
    std::string sha1_hash = sha1::sha1("Hello World!\n");
    std::cout << sha1_hash << std::endl;
    
    mandelbrot::demo(400,400,3,0,0,4,4);

    multivector::main();
    
    return 0;
}
