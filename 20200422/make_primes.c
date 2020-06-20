#include <stdio.h>
#include "util.h"

typedef unsigned long long u64;
static FILE* file;

int file_exists(const char * filename){
    /* try to open file to read */
    // FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

void sig_handler(int signo)
{
  if (signo == SIGINT){
    fclose(file);
    printf("received SIGINT\n");
    exit(0);
  }
}

typedef struct primes_t {
    u64* data;
    size_t length;
    size_t allocated;
} primes_t;

void primes_maybe_grow(primes_t* a)
{
	if (a->length == a->allocated){
		a->allocated *= 2;
		a->data = realloc(a->data, a->allocated * sizeof(u64));
        printf("OMG!!!\n");
	}
}

int main(int argc, char** argv){

    // int timeout = 1000;

    char* filename = "primes.dat";


  if (signal(SIGINT, sig_handler) == SIG_ERR)
      printf("\ncan't catch SIGINT\n");


    // If primes files exist then get primes from it
    // otherwise just start with a 2 as the first prime
    primes_t p;
    p.allocated = 1e6;
    p.data = malloc( p.allocated * sizeof(u64));
    p.length = 0;

    if (file_exists(filename)){
        printf("woo");
        string f = read_file(filename);
        strings s = split_destructive(f.data, "\n\r\t ");

        for (size_t i = 0; i < s.length; i++)
        {             
            printf("%s ", s.data[i]);       
            char* ptr;
            sscanf(s.data[i], "%llu", &p.data[i]); 
            primes_maybe_grow(&p);
            // p.data[i] = strtoll(s.data[i], &ptr, 10);
            p.length += 1;
        }
        printf("\n");

    }

    // printf("*last prime: %llu ", p.data[p.length-1]);
    
    if (p.length == 0){
        p.data[0] = 2;
        p.length = 1;
    }

	double t1 = get_time();

	file = fopen(filename, "a");

    u64 is_prime = 0;
    u64 a = p.data[p.length-1];
	for ( ; ; a++){
		is_prime = 1;
		for ( u64 i = 0; i < p.length; i++){
			if ( a%p.data[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime){
			p.data[p.length++] = a;
            primes_maybe_grow(&p);
            fprintf(file, "%llu ", p.data[p.length-1]);

			// printf("%d ", a);
		}


		if (get_time()-t1 >= 1){
			t1 = get_time();
			printf("last prime: %llu\r\n", p.data[p.length-1]);

            // if (t1 > timeout){ break; }
		}
	}

    fclose(file);

	// for ( u64 i = 0; i < p.length; i++){
	// 	printf("%d ", p.data[i]);
	// }

	return 0;
}
