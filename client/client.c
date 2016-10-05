#include "client.h"

#include <iniparser.h>
#include <stdio.h>
#include <logging.h>

static game_config_t *load_config() {
	game_config_t *config = calloc(1, sizeof(*config));
	dictionary *ini = iniparser_load("../client/settings.ini");

	if (!ini)
		log_error("Could not find settings file");

	config->win_height = iniparser_getint(ini, "window:height", 800);
	config->win_width = iniparser_getint(ini, "window:width", 600);
	config->env_grid = iniparser_getboolean(ini, "game:grid", false) != false;

	if (iniparser_getboolean(ini, "window:borderless", false))
		config->win_flags |= SDL_WINDOW_BORDERLESS;
	if (iniparser_getboolean(ini, "window:fullscreen", false))
		config->win_flags |= SDL_WINDOW_FULLSCREEN;

	iniparser_freedict(ini);
	return config;
}

static void destroy_config(game_config_t *config) {
	free(config);
}

static void game_init(game_t *game) {
	memset(game, 0, sizeof(*game));
	game->config = load_config();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		log_error("Couldn't initialize game. SDL Error: %s", SDL_GetError());

	game->window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		game->config->win_width,
		game->config->win_height,
		game->config->win_flags
	);

	if (!game->window)
		log_error("Couldn't create window. SDL Error: %s", SDL_GetError());

	if (!(game->renderer = SDL_CreateRenderer(game->window, -1, 0)))
		log_error("Couldn't create renderer. SDL Error: %s", SDL_GetError());

	game->buffer = SDL_CreateTexture(game->renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		8192,
		8192
	);

	if (!(game->buffer))
		log_error("Couldn't create texture. SDL Error: %s", SDL_GetError());

	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		log_warn("Couldn't disable cursor. SDL Error: %s", SDL_GetError());
}

static void game_loop(game_t *game) {
	SDL_Delay(25);
	free(game);
}

static void game_exit(game_t *game) {
	destroy_config(game->config);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}

int main() {
	game_t game;
	game_init(&game);
	game_loop(&game);
	game_exit(&game);
}
