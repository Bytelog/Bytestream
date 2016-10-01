#include <jemalloc/jemalloc.h>

#define __MEM_W
#include "mem.h"
#include "logging.h"

#define _ALLOC_WRAP(method, ...)						\
	void* alloc = method(__VA_ARGS__); 					\
	if(alloc == NULL) {									\
		log_error("'%s' failed to allocate!", #method);	\
	}													\
	return alloc;										\

void* _malloc_exit(size_t size) {
	_ALLOC_WRAP(malloc, size);
}

void* _calloc_exit(size_t number, size_t size) {
	_ALLOC_WRAP(calloc, number, size);
}

void* _realloc_exit(void* ptr, size_t size) {
	_ALLOC_WRAP(realloc, ptr, size);
}

void* _aln_alloc(size_t alignment, size_t size) {
	_ALLOC_WRAP(aligned_alloc, alignment, size);
}

