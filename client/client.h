#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <iniparser.h>
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

bool game_init(game_t *);
bool game_load_config(game_config_t *);
void game_loop(game_t *);
void game_exit(game_t *);
