#include "namespace.h"

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

struct namespace_t namespace = {
	.do_it = do_it, 
	.do_it_again = do_it_again
};
