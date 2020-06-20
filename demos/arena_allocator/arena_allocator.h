// clang -std=c11 -Weverything arena_allocator.c; ./a.out
#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>

void arena_make(size_t cap);
void* arena_allocate(size_t length);
void arena_recycle(void);
void arena_free(void);

#endif
