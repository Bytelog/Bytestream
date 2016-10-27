#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <common.h>
#include <coordinates.h>
#include <klib/kvec.h>
#include <mpack/mpack.h>

#define MAX_TILES (1<<26)

typedef struct map_t map_t;
typedef struct tile_t tile_t;
typedef struct object_t object_t;
typedef struct region_t region_t;

struct tile_t {
	uint32_t pos;
	uint16_t tile;
	bool active      : 1;
	uint8_t rotation : 5;
	uint16_t unused  : 10;
};

struct region_t {
	uint8_t type;
	bool active     : 1;
	uint32_t unused : 23;
	uint32_t start;
	uint32_t end;
	uint32_t data[3];
};

struct object_t {
	vec3_t position;
};

struct map_t {
	char name[64];
	uint16_t bounds[3];
	kvec_t(tile_t) tiles;
	kvec_t(region_t) regions;
	kvec_t(object_t) objects;
};

//bool compress_data(char **, size_t *length);
//bool decompress_data(char **data, size_t *length);
bool write_file(const char *path, const void *data, size_t length);
bool read_file(const char *path, void *data, size_t *length);

// add const qualifier
bool write_map(const char *path, map_t *map);
bool read_map(const char *path, map_t *map);
