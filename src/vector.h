/*
Generic resizeable vector.
Compile with no-cast-align warnings

clang -Weverything -Wno-cast-align
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector_t {
	void* data;
	size_t length;
	size_t allocated;
    size_t size;
} vector_t;

vector_t vector_make(size_t n, size_t s);
void vector_free(vector_t f);
vector_t maybe_grow(vector_t f);

