/*
clang -Weverything a.c arena_allocator.h types.h ; ./a.out
*/

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "util.h"
#include "multivector.h"
#include "mandelbrot.h"
// #include "misc.h"

int main(int argc, char** argv)
{
    // ./a.out split "alskdjfkslad kfjasklf ajfd" " "
    // ./a.out multivector
    // ./a.out mandelbrot
    if ( argc < 2 ) { 
        printf("usage: ./a.out something.  Look at the source\n");
        return -1;
    }

    if ( strcmp(argv[1], "split") == 0 ){
        split_main(argc, argv);
    } else if ( strcmp(argv[1], "multivector") == 0 ){
        mv_main();
    } else if ( strcmp(argv[1], "mandelbrot") == 0 ){
        // mandelbrot_main(argc, argv);
        mandelbrot_simple(1000,1000,0,0,4,4);
    }

   return 0;
}

