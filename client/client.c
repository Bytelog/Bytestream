#include <stdlib.h>
#include <stdio.h>
#include <sds/sdsalloc.h>
#include <sds/sds.h>
#include <coordinates.h>

int main() {
    vec3_t x = { .x = 5, .y = 6, .z = 8 };
    sds s = sdsnew("foo");
    printf("%s\n", s);
    sdsfree(s);
}
