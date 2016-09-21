#pragma once

typedef struct vec3_t vec3_t;

struct vec3_t {
	float x;
	float y;
	float z;
};

/**
 * Convert a cartesian coordinate to isometric
 *
 * @v source vector
 * @d distance transformation vector
 * @s scale transformation vector
 */
vec3_t coord_to_iso(vec3_t v, vec3_t d, vec3_t s);

/**
 * Convert an isometric coordinate to cartesian
 *
 * @v source vector
 * @d distance transformation vector
 * @s scale transformation vector
 */
vec3_t coord_from_iso(vec3_t v, vec3_t d, vec3_t s);
