/*
demo_vector
clang -Weverything -Wno-cast-align vector_t.h demo_vector.c ; ./a.out

Basically it's a struct with a void* array in it called data.  To use it you need to cast the void*
to something you'd prefer.  Like a sandwich

    vector_t a = vector_make(1000 * sizeof(sandwich_t));

To make things prettier we can use a macro for the casts

    #define sandwich_vector(a) ((sandwich_t*)a.data)

Push or append items

    sandwich_vector(a)[a.length++] = 3;
    a = maybe_grow(a);

To remove from the end 

    a.length--;

To delete all of the things

    a.length = 0;

To free 

    vector_free(a);

*/
#include "vector.h"
#include "basic.h"


// Define a vector type
typedef enum bread_t { white_bread, brown_bread, weird_vegan_bread, carb_free_bread, cardboard } bread_t;
typedef struct sandwich_t { 
    int ham; int lettuce; bread_t bread; } sandwich_t;
#define sandwich_vector(a) ((sandwich_t*)a.data)

void print_sandwich(sandwich_t a)
{
    printf("sandwich(ham: %d lettuce: %d bread: %d) \n", a.ham, a.lettuce, a.bread );
}
vector_t add_sandwich(vector_t a, sandwich_t b)
{
    sandwich_vector(a)[a.length++] = b;
    int old_length = a.length;
    a = maybe_grow(a);
    if ( old_length != a.length ) puts("realloc!!!");
    return a;
}


// Define another vector type
#define int_vector(o) ((int*)o.data)
vector_t add_integer(vector_t o, int i)
{
    int_vector(o)[o.length++] = i;
    o = maybe_grow(o);
    return o;
}

// Demo stuff
int main(void)
{
    // make a vector_t
    #define N 10
    vector_t basket = vector_make(N, sizeof(sandwich_t));

    // make too many sandwiches
    for (int i = 0; i < 10 * N; i+=1){
        // make a sandwich
        sandwich_t a; 
        a.ham = i; a.lettuce = 2*i; a.bread = white_bread;

        basket = add_sandwich(basket, a);
    }
    
    // print the sandwiches
    for (size_t i = 0; i < basket.length; i+=1){
        print_sandwich( sandwich_vector(basket)[i] ); 
        // brilliant metaphor is starting to break down
    }

    vector_free(basket);




    // string f; strings s; vector_t o;

    // f = read_file("demo_vector.c");
    // string str = string_copy(f);
    // s = string_split_destructive(f.data,"\r\n");
    
    // o = vector_make(1, sizeof(int));

    // printf("allocated: %d ", o.allocated );

    // // add integers
    // for (int i = 0; i < s.length; i++){
    //     add_integer(o,i);
    // }

    // for (int i = 0; i < s.length; i++) {
    //     printf("%d ", int_vector(o)[i]);
    // }
    // printf("allocated: %d ", o.allocated );
    


    return 0;
}

#undef T
#undef vector_t
#undef vector_format
