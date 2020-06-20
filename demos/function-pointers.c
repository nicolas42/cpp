// gcc concurrent_factorial.c && ./a.out 1 2 3 4 5 6 7

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int sum = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add1_locked(void* arg)
{
	pthread_mutex_lock(&mutex);
	sum += 1;
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

void* add1(void* arg)
{
	// pthread_mutex_lock(&mutex);
	sum += 1;
	// pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num 1> <num 2> ... <num-n>\n", argv[0]);
		exit(-1);
	}
	int num_threads = atoll(argv[1]);
	int num_args = argc - 1;

	int locked = 0;
	if (num_args >= 2 && strcmp(argv[2], "locked") == 0){
		locked = 1;
	}


	void* (*thread_function)(void* arg) = add1;

	// if (locked) {
	// 	thread_function = add1_locked;
	// } else {
	// 	thread_function = add1;
	// }


	// Launch threads
	pthread_t tids[num_threads];
	for (int i = 0; i < num_threads; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, thread_function, NULL);
	}

	// Wait until thread is done its work
	for (int i = 0; i < num_threads; i++) {
		pthread_join(tids[i], NULL);
	}
	printf("Result is %d\n", sum);

}
