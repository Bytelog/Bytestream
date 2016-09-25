#include "rand.h"

#include <stdio.h>
#include <time.h>

rand_t *rand_init() {
	uint64_t seed;
	FILE *urandom;

	if ((urandom = fopen("/dev/urandom", "r")) == NULL) {
		fprintf(stderr, "rand_init: cannot open /dev/urandom. Using fallback\n");
		goto error_seed;
	}

	if (fread(&seed, sizeof(seed), 1, urandom) != 1) {
		fprintf(stderr, "rand_init: cannot read /dev/urandom. Using fallback\n");
		goto error_seed;
	}

	fclose(urandom);
	return rand_seed(seed);

error_seed:
	if (urandom != NULL)
		fclose(urandom);

	clearerr(urandom);
	return rand_seed(time(0));
}

rand_t *rand_seed(uint64_t seed) {
	return kr_srand(seed);
}

float rand_float(rand_t *ctx) {
	// Single precision: 24 digits, add one to make the range exclusive
	return (rand_uint(ctx) >> 40) * (float) (1.0 / (16777216.0 + 1));
}

double rand_double(rand_t *ctx) {
	// Double precision: 53 digits, add one to make the range exclusive
	return (rand_uint(ctx) >> 11) * (1.0 / (9007199254740992.0 + 1));
}

uint64_t rand_uint(rand_t *ctx) {
	return kr_rand(ctx);
}

int64_t rand_int(rand_t *ctx) {
	return (int64_t) rand_uint(ctx);
}

int64_t rand_range(rand_t *ctx, int64_t min, int64_t max) {
	uint64_t number;
	uint64_t range = (uint64_t) (max - min);
	uint64_t buckets = UINT64_MAX / range;
	uint64_t limit = buckets * range;

	// Break the RNG into fair buckets, discarding overflow
	do { number = rand_uint(ctx); } while (number >= limit);

	return min + (int64_t) (number / buckets);
}

double rand_normal(rand_t *ctx) {
	return kr_normal(ctx);
}
