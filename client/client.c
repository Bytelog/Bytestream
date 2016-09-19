#include <stdlib.h>
#include <stdio.h>
#include <sds/sdsalloc.h>
#include <sds/sds.h>
#include <coordinates.h>
#include <rand.h>
#include <klib/kvec.h>

int main() {
    vec3_t x = { .x = 5, .y = 6, .z = 8 };
    sds s = sdsnew("foo");
    printf("%s\n", s);
    sdsfree(s);

    kvec_t(int) array;
    kv_init(array);
    for (int j = 0; j < 10; ++j)
        kv_push(int, array, j);
    kv_destroy(array);

    rand_t *rng = rand_init();

    for (int i = 0; i < 10; ++i) {
        printf("%.24g\n", rand_float(rng));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%.53g\n", rand_double(rng));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%zu\n", rand_uint(rng));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%zd\n", rand_int(rng));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%zd\n", rand_range(rng, 3, 6));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%zd\n", rand_range(rng, -12, -2));
    }

    for (int i = 0; i < 10; ++i) {
        printf("%zd\n", rand_range(rng, -2, 2));
    }
}
