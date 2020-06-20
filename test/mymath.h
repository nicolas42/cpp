#ifndef MATH_H
#define MATH_H

#include <stdio.h>
#include "int_array.h"

double math_chance_of_collision(double items, double places);
int math_is_prime(int a);
int math_make_primes(struct int_array* primes, int primes_length);
int math_main(int argc, char **argv);

#endif



