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
		log_warn("Could not write to file %s", path);
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}

bool read_file(const char *path, void *data, size_t *length) {
	FILE *file = NULL;

	if (!(file = fopen(path, "rb"))) {
		log_pwarn("Could not open %s, mode rb", path);
		return false;
	}

	if (fseek(file, 0, SEEK_END))
		goto error_read;

	if ((*length = (size_t) ftell(file)) == (size_t) -1L)
		goto error_read;

	rewind(file);
	data = malloc(*length);

	if (fread(data, 1, *length, file) != *length) {
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

bool write_map(const char *path, map_t *map) {
	char *data;
	size_t size;
	mpack_writer_t writer;
	mpack_writer_init_growable(&writer, &data, &size);

	mpack_start_map(&writer, 5);

	mpack_write_cstr(&writer, "name");
	mpack_write_cstr(&writer, map->name);

	mpack_write_cstr(&writer, "bounds");
	mpack_start_array(&writer, ARRAY_COUNT(map->bounds));
	for (size_t i = 0; i < ARRAY_COUNT(map->bounds); ++i)
		mpack_write_u16(&writer, map->bounds[i]);
	mpack_finish_array(&writer);

	mpack_write_cstr(&writer, "tiles");
	mpack_start_array(&writer, kv_size(map->tiles));
	for (size_t i = 0; i < kv_size(map->tiles); ++i) {
		tile_t tile = kv_A(map->tiles, i);
		mpack_start_array(&writer, 3);
		mpack_write_u32(&writer, tile.pos);
		mpack_write_u16(&writer, tile.tile);
		uint16_t bitfields = 0;
		bitfields |= (tile.active << 0);
		bitfields |= (tile.rotation << 1);
		mpack_write_u16(&writer, bitfields);
		mpack_finish_array(&writer);
	}
	mpack_finish_array(&writer);

	mpack_write_cstr(&writer, "regions");
	mpack_start_array(&writer, kv_size(map->regions));
	mpack_finish_array(&writer);

	mpack_write_cstr(&writer, "objects");
	mpack_start_array(&writer, kv_size(map->objects));
	mpack_finish_array(&writer);

	mpack_finish_map(&writer);
	mpack_writer_destroy(&writer);

	write_file(path, data, size);
	free(data);

	// TODO: Add handling
	return true;
}

bool read_map(const char *path, map_t *map) {
	//char *data;
	//size_t size;
	uint32_t count;
	//read_file(path, data, size);
	mpack_reader_t reader;
	mpack_reader_init_file(&reader, path);

	mpack_expect_map_match(&reader, 5);

	mpack_expect_cstr_match(&reader, "name");
	mpack_expect_cstr(&reader, map->name, ARRAY_COUNT(map->name));

	mpack_expect_cstr_match(&reader, "bounds");
	mpack_expect_array_match(&reader, ARRAY_COUNT(map->bounds));
	for (size_t i = 0; i < ARRAY_COUNT(map->bounds); ++i)
		map->bounds[i] = mpack_expect_u16(&reader);
	mpack_done_array(&reader);

	mpack_expect_cstr_match(&reader, "tiles");
	mpack_expect_array_max_or_nil(&reader, MAX_TILES, &count);
	kv_init(map->tiles);
	for (size_t i = 0; i < count; ++i) {
		tile_t tile;
		mpack_expect_array_match(&reader, 3);
		tile.pos = mpack_expect_u32(&reader);
		tile.tile = mpack_expect_u16(&reader);
		uint16_t bitfields = 0;
		bitfields = mpack_expect_u16(&reader);
		tile.active = (bitfields >> 0) & 0x01;
		tile.rotation = (bitfields >> 1) & 0x1F;
		mpack_done_array(&reader);
		kv_push(tile_t, map->tiles, tile);
	}
	mpack_done_array(&reader);

	mpack_expect_cstr_match(&reader, "regions");
	mpack_expect_array_max_or_nil(&reader, MAX_TILES, &count);
	mpack_done_array(&reader);

	mpack_expect_cstr_match(&reader, "objects");
	mpack_expect_array_max_or_nil(&reader, MAX_TILES, &count);
	mpack_done_array(&reader);

	mpack_done_map(&reader);
	mpack_reader_destroy(&reader);

	return true;
}

