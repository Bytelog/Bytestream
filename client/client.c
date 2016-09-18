#include <stdlib.h>
#include <stdio.h>
#include <sds/sdsalloc.h>
#include <sds/sds.h>
#include <coordinates.h>
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
}
