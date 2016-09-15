#pragma once

typedef struct vec3_t vec3_t;

struct vec3_t {
  float x;
  float y;
  float z;
};

vec3_t scale(vec3_t v, vec3_t s);
vec3_t translate(vec3_t v, vec3_t d);
vec3_t map(vec3_t);
vec3_t unmap(vec3_t);
vec3_t to_iso(vec3_t v, vec3_t d, vec3_t s);
vec3_t from_iso(vec3_t v, vec3_t d, vec3_t s);