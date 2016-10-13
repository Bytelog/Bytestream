#include "client.h"

#include <iniparser.h>
#include <stdio.h>
#include <logging.h>
#include <klib/kvec.h>
#include <coordinates.h>

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

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		log_error("Could not initialize SDL_image: %s", IMG_GetError());

	game->window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		game->config->win_width,
		game->config->win_height,
		game->config->win_flags
	);

	if (!game->window)
		log_error("Couldn't create window. SDL Error: %s", SDL_GetError());

	if (!(game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_SOFTWARE)))
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
	SDL_Surface *image = IMG_Load("../data/Sprites/Grass/ISO_Tile_Dirt_01_Grass_01.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, image);
	SDL_Rect zz = { 0, 0, 800, 600 };

	SDL_FreeSurface(image);
	SDL_Event e;

	kvec_t(vec3_t) tiles;
	kv_init(tiles);

	for (int i = 0; i < 5; ++i) {
		vec3_t v = { 0, 0, 0 };
		vec3_t s = { 34, 34, 34 };
		vec3_t d = { i % 32, i / 32, 0};
		vec3_t r = coord_to_iso(v, s, d);
		kv_push(vec3_t, tiles, r);
	}

	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				goto cleanup;
		}

		SDL_SetRenderTarget(game->renderer, game->buffer);
		SDL_SetRenderDrawColor(game->renderer, 25, 25, 25, 0xFF);
		SDL_RenderClear(game->renderer);

		for (int i = 0; i < kv_size(tiles); ++i) {
			SDL_Rect x = {kv_A(tiles, i).x, kv_A(tiles, i).y, 74, 82};
			log_info("x: %d, y: %d", kv_A(tiles, i).x, kv_A(tiles, i).y);
			SDL_RenderCopy(game->renderer, texture, NULL, &x);
		}

		SDL_SetRenderTarget(game->renderer, NULL);
		SDL_RenderCopy(game->renderer, game->buffer, &zz, NULL);
		SDL_RenderPresent(game->renderer);
		SDL_Delay(25);
	}

cleanup:
	SDL_DestroyTexture(texture);
	return;
}

static void game_exit(game_t *game) {
	destroy_config(game->config);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	IMG_Quit();
	SDL_Quit();
}

int main() {
	game_t game;
	game_init(&game);
	game_loop(&game);
	game_exit(&game);
}
