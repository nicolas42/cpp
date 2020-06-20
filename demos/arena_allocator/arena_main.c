#include "arena_allocator.h"

// Test type
typedef double* multivector_t;
static int multivector_length = 8;

multivector_t vector(double a, double b, double c)
{
    multivector_t arr;
    arr = (multivector_t)arena_allocate(sizeof(arr));

    for (size_t i = 0; i < multivector_length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

int main(void)
{
    arena_make((int)1e6);

    multivector_t a;
    a = vector(1,2,3);

    for (size_t i = 0; i < multivector_length; i++) {
        printf("%.2f ", a[i]);
    }
    
    return 0;
}
