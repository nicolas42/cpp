/*
clang  lib.a -Isrc demos/mandelbrot-demo.c ; ./a.out ; open out.ppm 
*/
#include "mandelbrot.h"

int main(int argc, char** argv){
    mandelbrot_main(argc, argv);
    return 0;
}
