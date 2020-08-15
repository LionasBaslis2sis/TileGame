#include "assets.hpp"

Assets::~Assets() {
	// free all SDL_Texture objects
	SDL_DestroyTexture(player);
}

constexpr Assets::Assets() noexcept {

}


void Assets::init(SDL_Renderer* renderer) noexcept {
	// load all SDL_Texture objects
	player = loadTexture(renderer, "res/player.png");
}

Assets& Assets::get() noexcept {
	static Assets instance;
	return instance;
}