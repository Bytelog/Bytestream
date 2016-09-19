#pragma once

#include <klib/kmath.h>

// The context structure for the PRNG
typedef struct _krand_t rand_t;

// Set up a context with a random seed
rand_t *rand_init(void);

/**
 * Set up a context with a given seed
 *
 * @seed Number to initialize the PRNG with
 */
rand_t *rand_seed(uint64_t seed);

// Generate a random floating point number in [0, 1)
float rand_float(rand_t *ctx);

// Generate a random, double precision floating point number in [0, 1)
double rand_double(rand_t *ctx);

// Generate a random non-negative integer in [0, UINT64_MAX]
uint64_t rand_uint(rand_t *ctx);

// Generate a random integer in [INT64_MIN, INT64_MAX]
int64_t rand_int(rand_t *ctx);

// Generate a random integer in [min, max)
int64_t rand_range(rand_t *ctx, int64_t min, int64_t max);

// Generate a random number from a normal distribution
double rand_normal(rand_t *ctx);

/**
 * Shuffle an array
 *
 * @arr Array to shuffle
 * @len Number of elements in the array
 */
#define rand_shuffle(ctx, arr, len) do {                        \
  if ((len) > 1) {                                              \
    size_t i, j;                                                \
    for (i = 0; i < (len) - 1; ++i) {                           \
        j = (size_t) rand_range((ctx), 0, (int64_t) (len));     \
        if (i == j) continue;                                   \
        (arr)[i] = (arr)[i] ^ (arr)[j];                         \
        (arr)[j] = (arr)[i] ^ (arr)[j];                         \
        (arr)[i] = (arr)[i] ^ (arr)[j];                         \
    }                                                           \
  }                                                             \
} while (0)                                                     \

/**
 * Pick a random element from an array
 *
 * @arr  Array to choose from
 * @len  Number of elements in the array
 */
#define rand_choice(ctx, arr, len) ((arr)[rand_range((ctx), 0, (len))])


