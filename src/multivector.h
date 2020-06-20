#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

/*
clang multivector.c -Weverything ; ./a.out
*/

/*
implements the multivector functions
init scalar vector bivector trivector vector_spherical 
geometric_product mul rotate rot 
print print_scalar print_vector print_bivector print_trivector 
arena_make arena_allocate arena_recycle arena_free arena arena_length arena_capacity 

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
// #include "short_type.h"
// #include "types.h"

#define multivector_length 8
typedef double* multivector_t;
static unsigned int multivector_size = 8 * sizeof(double);

multivector_t multivector_init(void);
multivector_t multivector_scalar(double arg);
multivector_t multivector_vector(double a, double b, double c);
multivector_t multivector_bivector(double a, double b, double c);
multivector_t multivector_trivector(double arg);
multivector_t multivector_vector_spherical(double r, double theta, double phi);

multivector_t multivector_geometric_product(multivector_t a, multivector_t b);
multivector_t multivector_mul(int num, ...);

multivector_t multivector_rotate(multivector_t v, multivector_t a, multivector_t b);
multivector_t multivector_rot(multivector_t a, multivector_t b);

void multivector_print(multivector_t a);
void multivector_print_scalar(multivector_t a);
void multivector_print_vector(multivector_t a);
void multivector_print_bivector(multivector_t a);
void multivector_print_trivector(multivector_t a);

void multivector_arena_make(size_t cap);
multivector_t multivector_arena_allocate(void);
void multivector_arena_recycle(void);
void multivector_arena_free(void);
int multivector_main(void);

static multivector_t multivector_arena;
static size_t multivector_arena_size;
static size_t multivector_arena_allocated;

#endif
