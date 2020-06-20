#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
// #include "../types.h"

#define number_of_iterations 1e7

typedef unsigned long long u64;

double get_time(void){
	return clock()/(double)CLOCKS_PER_SEC;
}

typedef struct thread_arg {
	u64 arg;
	u64 res;
} thread_arg;

// Thread function to generate sum of 0 to N
void* thread_function(void* arg)
{
    thread_arg *a = (thread_arg*) arg;
    // now I'm a real boy

    for (size_t i = 0; i < number_of_iterations; i++){

        u64 sum = 1;
        for (long long i = 1; i <= a->arg; i++) {
            sum *= i;
        }
        a->res = sum;
    }
    

	pthread_exit(0);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num 1> <num 2> ... <num-n>\n", argv[0]);
		exit(-1);
	}
	int nargs = argc - 1;


    double t1,t2;
    t1 = get_time();

	thread_arg targs[nargs];
	pthread_t tids[nargs];

	for (int i = 0; i < nargs; i++) {

		targs[i].arg = atoll(argv[i + 1]);
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tids[i], &attr, thread_function, &targs[i]);
	}

	// Wait for threads
	for (size_t i = 0; i < nargs; i++) {
    // for (int i = nargs-1; i >= 0 ; i -= 1 ){
		pthread_join(tids[i], NULL);
        printf("time: %.3f ", get_time() - t1 );
        printf("thread %lu. factorial %llu is %llu\n", i, targs[i].arg, targs[i].res);
        
	}

}
