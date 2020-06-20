/*
clang -Weverything arena_allocator.c; ./a.out
*/
#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H

#include <stdlib.h>

void arena_init(void);
void arena_make(size_t cap);
char* arena_allocate(size_t length);
void arena_recycle(void);
void arena_free(void);

#define default_arena_size 128

static char* arena;
static size_t arena_length;
static size_t arena_capacity;


void arena_init(void)
{
    arena_length = 0;
    arena_capacity = default_arena_size;
    arena = malloc(default_arena_size);
}


void arena_make(size_t cap)
{
    arena_length = 0;
    arena_capacity = cap;
    arena = malloc(cap);
}

char* arena_allocate(size_t length)
{
    char* offset;
    offset = arena + arena_length;

    // realloc on overflow
    if (arena_length + length > arena_capacity){
        arena_capacity *= 2;
        arena = realloc(arena, arena_capacity);
    }

    arena_length += length;
    return offset;
}

void arena_recycle(void)
{
    arena_length = 0;
}

void arena_free(void)
{
    free(arena);
}


#undef default_arena_size

#endif
