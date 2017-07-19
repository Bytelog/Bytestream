#pragma once

#include <jemalloc/jemalloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Byte aliases
typedef char          byte;
typedef unsigned char ubyte;

// Pointer aliases
typedef size_t    uptr;
typedef ptrdiff_t iptr;

// Signed integer aliases
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Unsigned integer aliases
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Floating point aliases
typedef float       f32;
typedef double      f64;
typedef long double f80;

// Math definitions
#define abs(a)   (((a)>0) ? (a) : -(a))min
#define min(a,b) (((a)<(b)) ? (a) : (b))
#define max(a,b) (((a)<(b)) ? (b) : (a))

// Array count
#define count(array) (sizeof(array) / sizeof(array[0]))

// Performance macros
#define ALWAYS_INLINE inline __attribute__((always_inline))
#define LIKELY_IS(x, y) __builtin_expect((x), (y))
#define LIKELY(x)   LIKELY_IS(!!(x), 1)
#define UNLIKELY(x) LIKELY_IS((x), 0)

// Malloc wrappers
#define _ALLOC_WRAP(method, ...) \
    void* alloc = method(__VA_ARGS__); \
    if (UNLIKELY(alloc == NULL)) { \
        fputs("Could not allocate memory '" #method "'\n", stderr); \
        abort(); \
    } \
return alloc;

inline void *malloc_exit(size_t size) {
    _ALLOC_WRAP(malloc, size);
}

inline void *calloc_exit(size_t number, size_t size) {
    _ALLOC_WRAP(calloc, number, size);
}

inline void *realloc_exit(void *ptr, size_t size) {
    _ALLOC_WRAP(realloc, ptr, size);
}

inline void *aligned_alloc_exit(size_t alignment, size_t size) {
    _ALLOC_WRAP(aligned_alloc, alignment, size);
}

#define malloc  malloc_exit
#define calloc  calloc_exit
#define realloc realloc_exit
#define aligned_alloc aligned_alloc_exit

// Benchmarking functions
clock_t watch_clock;
inline void watch_start() {
    watch_clock = clock();
}

inline f64 watch_peek() {
    return ((f64)(clock() - watch_clock) / CLOCKS_PER_SEC);
}
