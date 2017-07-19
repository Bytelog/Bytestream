/*
------------------------------------------------------------------------------
isaac64.c: My random number generator for 64-bit machines.
By Bob Jenkins, 1996.  Public Domain.

Adapted isaac (32-bit variant) improvements for the 64-bit variant.
By Dylan Alllbee, 2017.  Public Domain.
------------------------------------------------------------------------------
*/

#include "isaac64.h"

#define ind(mm,x)  (*(uint64_t *)((uint8_t *)(mm) + ((x) & ((RANDSIZ-1)<<3))))
#define rngstep(mix, a, b, mm, m, m2, r, x) { \
    x = *m; \
    a = (mix) + *(m2++); \
    *(m++) = y = ind(mm, x) + a + b; \
    *(r++) = b = ind(mm, y >> RANDSIZL) + x; \
}

void isaac64(struct rand_ctx *ctx) {
    register uint64_t a, b, x, y, *m, *mm, *m2, *r, *mend;
    mm = ctx->mem;
    r = ctx->rsl;
    a = ctx->a;
    b = ctx->b + (++ctx->c);
    for (m = mm, mend = m2 = m + (RANDSIZ/2); m < mend; ) {
        rngstep(~(a ^ (a << 21)), a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a >> 5)  , a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a << 12) , a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a >> 33) , a, b, mm, m, m2, r, x);
    }
    for (m2 = mm; m2 < mend; ) {
        rngstep(~(a ^ (a << 21)), a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a >> 5)  , a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a << 12) , a, b, mm, m, m2, r, x);
        rngstep(  a ^ (a >> 33) , a, b, mm, m, m2, r, x);
    }
    ctx->b = b;
    ctx->a = a;
}

#define mix(a, b, c, d, e, f, g, h) { \
     a -= e; f ^= (h >> 9 ); h += a; \
     b -= f; g ^= (a << 9 ); a += b; \
     c -= g; h ^= (b >> 23); b += c; \
     d -= h; a ^= (c << 15); c += d; \
     e -= a; b ^= (d >> 14); d += e; \
     f -= b; c ^= (e << 20); e += f; \
     g -= c; d ^= (f >> 17); f += g; \
     h -= d; e ^= (g << 14); g += h; \
}

/* if (flag==TRUE), then use the contents of rsl[] to initialize mm[]. */
void randinit(struct rand_ctx *ctx, bool flag) {
    ctx->a = ctx->b = ctx->c = 0;

    if (flag) {
        int i;
        uint64_t a, b, c, d, e, f, g, h;
        uint64_t *m, *r;
        m = ctx->mem;
        r = ctx->rsl;
        a = b = c = d = e = f = g = h = 0x9e3779b97f4a7c13LL;

        for (i = 0; i < 4; ++i) {
            mix(a, b, c, d, e, f, g, h);
        }

        for (i = 0; i < RANDSIZ; i += 8) {
            a += r[i  ]; b += r[i+1]; c += r[i+2]; d += r[i+3];
            e += r[i+4]; f += r[i+5]; g += r[i+6]; h += r[i+7];
            mix(a, b, c, d, e, f, g, h);
            m[i  ] = a; m[i+1] = b; m[i+2] = c; m[i+3] = d;
            m[i+4] = e; m[i+5] = f; m[i+6] = g; m[i+7] = h;
        }

        for (i = 0; i < RANDSIZ; i += 8) {
            a += m[i  ]; b += m[i+1]; c += m[i+2]; d += m[i+3];
            e += m[i+4]; f += m[i+5]; g += m[i+6]; h += m[i+7];
            mix(a, b, c, d, e, f, g, h);
            m[i  ] = a; m[i+1] = b; m[i+2] = c; m[i+3] = d;
            m[i+4] = e; m[i+5] = f; m[i+6] = g; m[i+7] = h;
        }
    }

    isaac64(ctx);
    ctx->cnt=RANDSIZ;
}
