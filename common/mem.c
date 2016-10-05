#define __MEM_WRAP
#include "mem.h"

#include <stdio.h>

#define _ALLOC_WRAP(method, ...)									\
	printf("test\n");void* alloc = method(__VA_ARGS__); 								\
	if (alloc == NULL) {											\
		fputs("Could not allocate memory '" #method "'\n", stderr);	\
		abort();													\
	}																\
	return alloc;													\

void *malloc_exit(size_t size) {
	_ALLOC_WRAP(malloc, size);
}

void *calloc_exit(size_t number, size_t size) {
	_ALLOC_WRAP(calloc, number, size);
}

void *realloc_exit(void *ptr, size_t size) {
	_ALLOC_WRAP(realloc, ptr, size);
}

void *aligned_alloc_exit(size_t alignment, size_t size) {
	_ALLOC_WRAP(aligned_alloc, alignment, size);
}
