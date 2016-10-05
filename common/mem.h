#pragma once
#include <stdlib.h>

#ifndef __MEM_WRAP
#define malloc  malloc_exit
#define calloc  calloc_exit
#define realloc realloc_exit
#define aligned_alloc aligned_alloc_exit
#endif

void *malloc_exit(size_t size);
void *calloc_exit(size_t number, size_t size);
void *realloc_exit(void *ptr, size_t size);
void *aligned_alloc_exit(size_t alignment, size_t size);
