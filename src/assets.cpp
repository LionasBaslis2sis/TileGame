#include "assets.hpp"

Assets::~Assets() {
	// free all SDL_Texture objects
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(grass_tile);
}

void Assets::init(SDL_Renderer* renderer) noexcept {
	// load all SDL_Texture objects
	player = loadTexture(renderer, "res/player.png");
	grass_tile = loadTexture(renderer, "res/grass_tile.png");
}

Assets& Assets::get() noexcept {
	static Assets instance;
	return instance;
}