#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct game_t game_t;
typedef struct game_config_t game_config_t;

struct game_t {
	game_config_t *config;
	SDL_Window *window;
	SDL_Texture *buffer;
	SDL_Renderer *renderer;
	SDL_Rect clip;
};

struct game_config_t {
	int win_height;
	int win_width;
	uint32_t win_flags;
	bool env_grid : 1;
};
