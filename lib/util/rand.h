#pragma once

#include <standard.h>
#include <util/isaac/isaac64.h>

/**
 * Seeds an rng context with a string
 */
void rand_seed(struct rand_ctx* ctx, byte seed[RANDSIZ]);

/**
 * Allocates and seeds an rng context with system random.
 */
struct rand_ctx* rand_new();

/**
 * Returns a uniformly distributed integer.
 */
u64 rand_u64(struct rand_ctx* ctx);

/**
 * Returns a uniformly distributed f64 in the range of [0.0, 1.0].
 */
f64 rand_f64(struct rand_ctx* ctx);

/**
 * Returns a uniformly distributed f64 in the range of [0.0, 1.0].
 */
f32 rand_f32(struct rand_ctx* ctx);

/**
 * Returns a uniformly distributed int in the range [m, n].
 * The result has an insignificant bias.
 */
i32 rand_range(struct rand_ctx* ctx, i32 m, i32 n);

/**
 * Returns a normally distributed f64 in the range [FLT_MIN, FLT_MAX].
 */
f64 rand_normal(struct rand_ctx* ctx, f64 mean, f64 sttdev);

/**
 * Returns a standard normally distributed f64 in the range [FLT_MIN, FLT_MAX].
 */
f64 rand_standard(struct rand_ctx* ctx);
