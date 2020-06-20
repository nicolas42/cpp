/*
clang namespace.c namespace_demo.c ; ./a.out

To namespace in c 
define a struct full of function pointers
the declare it as an external global instance
then initialize it with the approprite pointers after the 
functions are defined in the .c file
*/

#include "namespace.h"

int main(void)
{
	namespace.do_it();
	namespace.do_it_again();

	return 0;
}
