#include <stdio.h>
#include <time.h>
#include "array.h"

int is_prime(int a){
	
	// int sqrta = (int) ceil(sqrt( (double) a ));

	for ( int i = 2; i < a; i++ ){
		if ( a%i == 0){
			return 0;
		}
	}
	return 1;
}


int make_primes(ARRAY* primes, int primes_length){

	for (int a = 3; primes->length < primes_length; a++){
		if (is_prime(a)){
			array_add(primes, (double)a);
		}
	}
	return 0;
}

// int main(int argc, char **argv)
// {
// 	puts("Generating primes...");

// 	ARRAY p; array_init(&p);
// 	make_primes(&p, 1000);

// 	for (int i = 0; i < 1000; i++)
// 	{
// 		printf("%d ", (int)p.data[i]);
// 	}
	

// 	return 0;
// }

