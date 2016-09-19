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
