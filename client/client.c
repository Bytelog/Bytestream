#include <stdlib.h>
#include <stdio.h>
#include <sds/sdsalloc.h>
#include <sds/sds.h>
#include <coordinates.h>
#include <rand.h>
#include <klib/kvec.h>

#include <mem.h>
#include <logging.h>


int main() {
	void* m_test = malloc(1024*64);
	void* c_test = calloc(0x42, 1024*64);
	void* r_test = realloc(m_test, 1024*32);

	log_debug("Addrs: %p, %p, %p", m_test, c_test, r_test);


	free(m_test);
	free(c_test);
	free(r_test);
	return 0;
}
