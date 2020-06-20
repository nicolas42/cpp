#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

double get_time(void){
	return clock()/(double)CLOCKS_PER_SEC;
}

void count_ticks(double max_time){

	double next_print_time = 1.0;
	
	for (int i = 0; i < 1e9; i++)
	{

		/* Print every second */
		if (time_elapsed() > next_print_time){
			next_print_time++;
			printf("%f ", time_elapsed());
			// printf("time_elapsed: %f ticks(): %lu\r\n", time_elapsed(), clock()); 
			fflush(stdout); 
			// protop: some buffers don't flush without a newline
		}

		if (time_elapsed() >= max_time){
			break;
		}
		
	}
}
	

int count_ticks_main(void)
{
	puts("Counting ticks...");
	count_ticks(3);
	return 0;
}

double chance_of_collisions(double a, double b){

	double s = 1;
	
	for (double i = a; i > (a - b); i -= 1){
		s *= i / a;
		// printf("%.0f/%.0f", i, a);
	}

	return 1 - s;

}

void chance_of_collision_usage(void){
	printf("Usage: chance-of-collision [slots] [items]\r\n");
}

int chance_of_collision_main(int argc, char **argv)
{

	double pigeon_holes = 365;
	double pigeons = 20;
	double P = -1;
	
	switch (argc){
	case 1:
		chance_of_collision_usage(); 
		return 1;
		break;
	case 2:
		pigeons = atoi(argv[1]); 
		break;
	case 3:
		pigeons = atoi(argv[1]); 
		pigeon_holes = atoi(argv[2]);
		break;
	default:
		chance_of_collision_usage(); 
		return 1;
		break;
	}

	P = chance_of_collisions(pigeon_holes, pigeons);

	printf("chance-of-collision of %.0f items in %.0f positions: %f\r\n", pigeons, pigeon_holes, P);


	return 0;
}

uint64_t prime_factors(uint64_t arg)
{
	// if the input is divisible by 2 then divide it by 2 
	// if it's divisible by 3 then divide it by 3
	// and so on until the end of that number

	// variables
	// the original prime number arg
	// the divisor d

	uint64_t i = 2;

	while (arg > 1){
		// fputc('.',stdout);	
		if (arg % i == 0){
			arg /= i;
			printf("%llu ", i);
		} else {
			i++;
		}
	}

	return 0;
}

int prime_factors_main(int argc, char** argv)
{

	uint64_t arg = 999;
	char* ptr;
	if (argc > 1){
		arg = strtoll(argv[1], &ptr, 10);
	}
	prime_factors(arg);
	return 0;
}

void hello_world(void)
{
	printf("Hello World!\n");
}

#endif
