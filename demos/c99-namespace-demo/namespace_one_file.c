// clang namespace_one_file.c ; ./a.out

// === header file

#ifndef OBJECT_DEMO_H
#define OBJECT_DEMO_H

#include <stdio.h>
#include <math.h>

#endif


// === c file

// #include "namespace.h"

void do_it(void);
void do_it_again(void);

void do_it(void)
{
	printf("Wow, you really did it\n");
}

void do_it_again(void)
{
	printf("You did it again!\n");
}


typedef struct namespace_t {
	void (*do_it)(void);
	void (*do_it_again)(void);	
}  namespace_t;

extern const struct namespace_t namespace;

const struct namespace_t namespace = {
	.do_it = do_it, 
	.do_it_again = do_it_again
};


// === main file

#include "namespace.h"

int main(void)
{
	namespace.do_it();
	namespace.do_it_again();

	return 0;
}
