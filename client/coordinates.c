#include "coordinates.h"

static vec3_t scale(vec3_t v, vec3_t s) {
    return (vec3_t) {
        .x = v.x * s.x,
        .y = v.y * s.y,
        .z = v.z * s.z
    };
}

static vec3_t translate(vec3_t v, vec3_t d) {
    return (vec3_t) {
        .x = v.x + d.x,
        .y = v.y + d.y,
        .z = v.z + d.z
    };
}

// Performs cartesian -> isometric transform
static vec3_t map(vec3_t v) {
    return (vec3_t) {
        .x = v.x + v.y,
        .y = (v.y - v.x) / 2 + v.z,
        .z = v.z
    };
}

// Performs isometric -> cartesian transform
static vec3_t unmap(vec3_t v) {
    return (vec3_t) {
        .x = v.x / 2 - v.y + v.z,
        .y = v.y + v.x / 2 - v.z,
        .z = v.z
    };
}

vec3_t coord_to_iso(vec3_t v, vec3_t d, vec3_t s) {
    return map(scale(translate(v, d), s));
}

vec3_t coord_from_iso(vec3_t v, vec3_t d, vec3_t s) {
    return translate(scale(unmap(v), s), d);
}
