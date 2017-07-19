/*
------------------------------------------------------------------------------
isaac64.h: definitions for a random number generator
Bob Jenkins, 1996, Public Domain
------------------------------------------------------------------------------
*/

#pragma once
#include <stdbool.h>
#include <stdint.h>

#define RANDSIZL   (8)
#define RANDSIZ    (1<<RANDSIZL)

/* context of random number generator */
struct rand_ctx {
  uint64_t cnt;
  uint64_t rsl[RANDSIZ];
  uint64_t mem[RANDSIZ];
  uint64_t a;
  uint64_t b;
  uint64_t c;
};

/*
------------------------------------------------------------------------------
 If (flag==TRUE), then use the contents of rsl[0..255] as the seed.
------------------------------------------------------------------------------
*/
void randinit(struct rand_ctx *ctx, bool flag);

void isaac64();


/*
------------------------------------------------------------------------------
 Call rand() to retrieve a single 64-bit random value
------------------------------------------------------------------------------
*/
#define _rand(ctx) \
    (!(ctx)->cnt-- ? \
        (isaac64(ctx), (ctx)->cnt=RANDSIZ-1, (ctx)->rsl[(ctx)->cnt]) : \
        (ctx)->rsl[(ctx)->cnt])
