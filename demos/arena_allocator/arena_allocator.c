#include <stdlib.h>
#include "arena_allocator.h"

static void* arena;
static size_t arena_length;
static size_t arena_capacity;


// === Arena Allocator =============

void arena_make(size_t cap)
{
    arena_length = 0;
    arena_capacity = cap;
    arena = malloc(cap);
}

void* arena_allocate(size_t length)
{
    void* offset;
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
