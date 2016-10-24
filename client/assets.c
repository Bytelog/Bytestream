#include "assets.h"

#include <errno.h>
#include <logging.h>

bool write_file(const char *path, const void *data, size_t length) {
	FILE *file;

	if (!(file = fopen(path, "wb"))) {
		log_pwarn("Could not open %s, mode wb", path);
		return false;
	}

	if (fwrite(data, 1, length, file) != length) {
		log_warn("Could not write to file %s");
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}

bool read_file(const char *filename, void *data, size_t length) {
	FILE *file = NULL;

	if (!(file = fopen(filename, "rb"))) {
		log_pwarn("Could not open %s, mode rb", path);
		return false;
	}

	if (fseek(file, 0, SEEK_END))
		goto error_read;

	if ((length = (size_t) ftell(file)) == -1L)
		goto error_read;

	rewind(file);
	data = malloc(length);

	if (fread(data, 1, length, file) != length) {
		free(data);
		goto error_read;
	}

	fclose(file);
	return true;

error_read:
	log_warn("Could not read file %s", path);
	fclose(file);
	return false;
}
