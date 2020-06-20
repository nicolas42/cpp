/*
Generic resizeable vector.
Compile with no-cast-align warnings

clang -Weverything -Wno-cast-align
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector {
	void* data;
	size_t length;
	size_t allocated;
    size_t size;
} vector;

#define T vector

T vector_make(size_t n, size_t s);
void vector_free(T f);
T maybe_grow(T f);

T vector_make(size_t n, size_t s)
{
    // make sure alignment is good. 
    // so an integer number of of size s fits inside
	// this will lead to slightly more being allocated
    while ( n % s != 0 ){ n += 1; }

	T f;
    f.size = s;
	f.length = 0;
	f.allocated = n;
	f.data = malloc(n*s);
	return f;
}

void vector_free(T f)
{
	free(f.data);
}

T maybe_grow(T f)
{
	if (f.length == f.allocated){
		f.allocated *= 2;
		f.data = realloc(f.data, f.allocated * f.size);
        puts("realloc!!!");
	}
    return f;
}


#undef T
