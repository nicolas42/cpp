#include "vector.h"

vector_t vector_make(size_t n, size_t s)
{
    // make sure alignment is good. 
    // so an integer number of of size s fits inside
	// this will lead to slightly more being allocated
    while ( n % s != 0 ){ n += 1; }

	vector_t f;
    f.size = s;
	f.length = 0;
	f.allocated = n;
	f.data = malloc(n*s);
	return f;
}

void vector_free(vector_t f)
{
	free(f.data);
}

vector_t maybe_grow(vector_t f)
{
	if (f.length == f.allocated){
		f.allocated *= 2;
		f.data = realloc(f.data, f.allocated * f.size);
	}
    return f;
}
