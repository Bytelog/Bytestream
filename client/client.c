#include "client.h"

#include <stdio.h>

bool game_init(game_t *game) {
  memset(game, 0, sizeof(*game));
  game->config = malloc(sizeof(game->config));

  if (!game_load_config(game->config))
    goto error_config;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    goto error_init;

  game->window = SDL_CreateWindow("Game",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    game->config->win_width,
    game->config->win_height,
    game->config->win_flags
  );

  if (!game->window)
    goto error_init;

  if (!(game->renderer = SDL_CreateRenderer(game->window, -1, 0)))
    goto error_init;

  game->buffer = SDL_CreateTexture(game->renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    8192,
    8192
  );

  if (!(game->buffer))
    goto error_init;

  if (SDL_ShowCursor(SDL_DISABLE) < 0)
    goto warning_init;

  return true;

warning_init:
  printf("Game initialization incomplete. SDL Error: %s\n", SDL_GetError());
  return true;

error_config:
  printf("Could not load configuration file");
  return false;

error_init:
  printf("Game initialization failed. SDL Error: %s\n", SDL_GetError());
  return false;
}

bool game_load_config(game_config_t *config) {
  memset(config, 0, sizeof(*config));
  dictionary *ini;

  if (!(ini = iniparser_load("../../client/settings.ini")))
    return false;

  config->win_height = iniparser_getint(ini, "window:height", 800);
  config->win_width = iniparser_getint(ini, "window:width", 600);
  config->env_grid = (bool) iniparser_getboolean(ini, "game:grid", false);

  if (iniparser_getboolean(ini, "window:borderless", false))
    config->win_flags |= SDL_WINDOW_BORDERLESS;
  if (iniparser_getboolean(ini, "window:fullscreen", false))
    config->win_flags |= SDL_WINDOW_FULLSCREEN;

  iniparser_freedict(ini);
  return true;
}

void game_loop(game_t *game) {
  SDL_Delay(25);
}

void game_exit(game_t *game) {
  free(game->config);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
}

int main() {
  game_t game;

  if (!game_init(&game))
    return EXIT_FAILURE;

  game_loop(&game);
  game_exit(&game);
}
