#include <stdlib.h>
#include <stdio.h>
#include <sds/sdsalloc.h>
#include <sds/sds.h>
#include <coordinates.h>
#include <rand.h>
#include <klib/kvec.h>

#include <logging.h>

int main() {

	log_debug("Hello, main @ %016x", &main);
	log_info("2+2 = %d", 4);
	log_warn("Danger will %s", "robinson");
	log_error("Boom~");


	vec3_t x = { .x = 5, .y = 6, .z = 8 };
	sds s = sdsnew("foo");
	printf("%s\n", s);
	sdsfree(s);

	kvec_t(int) array;
	kv_init(array);
	for (int j = 0; j < 10; ++j)
			kv_push(int, array, j);
	kv_destroy(array);

	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	rand_t *ctx = rand_init();
	for (int i = 0; i < 10; ++i) {
			printf("%d\n", arr[i]);
	}

	rand_shuffle(ctx, arr, 10);
	for (int i = 0; i < 10; ++i) {
			printf("%d\n", arr[i]);
	}
}
