#include "mymath.h"
#include <stdio.h>
#include <time.h>
#include "int_array.h"

// Calculate the chance of one or more collisions occuring when randomly putting
// a particular number of items intoa particular number of places
double mymath_chance_of_collision(double items, double places){

	double s = 1;
	
	for (double i = places; i > (places - items); i -= 1){
		s *= i / places;
		// printf("%.0f/%.0f", i, a);
	}

	return 1 - s;

}

int mymath_is_prime(int a){
	
	// int sqrta = (int) ceil(sqrt( (double) a ));

	for ( int i = 2; i < a; i++ ){
		if ( a%i == 0){
			return 0;
		}
	}
	return 1;
}


int mymath_make_primes(struct int_array* primes, int primes_length){

	for (int a = 3; primes->length < primes_length; a++){
		if (mymath_is_prime(a)){
			int_array_add(primes, (double)a);
		}
	}
	return 0;
}

int mymath_main(int argc, char **argv)
{
	int number_of_primes = 100;

	switch (argc)
	{
	case 2:
		number_of_primes = atoi(argv[1]);
		break;
	
	default:
		break;
	}

	struct int_array p; int_array_init(&p);
	mymath_make_primes(&p, number_of_primes);

	puts("Making primes...");
	for (int i = 0; i < number_of_primes; i++)
	{
		printf("%d ", (int)p.data[i]);
	}
	

	return 0;
}
