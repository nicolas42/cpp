#ifndef OBJECT_DEMO_H
#define OBJECT_DEMO_H

#include <stdio.h>
#include <math.h>

typedef struct namespace_t {
	void (*do_it)(void);
	void (*do_it_again)(void);	
}  namespace_t;

extern struct namespace_t namespace;

#endif