#include "assets.hpp"

Assets::~Assets() {
	
}

void Assets::cleanup() noexcept {
	// free all SDL_Texture objects
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(grass_tile);
	SDL_Log("Assets destructed\n");
}

void Assets::init(SDL_Renderer* renderer) noexcept {
	// load all SDL_Texture objects
	player = loadTexture(renderer, "res/player.png");
	grass_tile = loadTexture(renderer, "res/grass_tile.png");
	SDL_Log("Assets loaded\n");
}

Assets& Assets::get() noexcept {
	static Assets instance;
	return instance;
}