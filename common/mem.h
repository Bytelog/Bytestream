#pragma once
#include <stddef.h>

#ifndef __MEM_W
#define malloc  _malloc_exit
#define calloc  _calloc_exit
#define realloc _realloc_exit
#define aligned_alloc _aln_alloc
#endif

void* _malloc_exit(size_t size);
void* _calloc_exit(size_t number, size_t size);
void* _realloc_exit(void* ptr, size_t size);
void* _aln_alloc(size_t alignment, size_t size);
