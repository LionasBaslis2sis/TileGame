#include "assets.hpp"

Assets::~Assets() {
	
}

void Assets::cleanup() noexcept {
	// free all SDL_Texture objects
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(player_sheet);
	SDL_DestroyTexture(tiles);
	SDL_Log("Assets destructed\n");
}

void Assets::init(SDL_Renderer* renderer) noexcept {
	// load all SDL_Texture objects
	player = loadTexture(renderer, "res/player.png");
	player_sheet = loadTexture(renderer, "res/player_sheet.png");
	tiles = loadTexture(renderer, "res/tiles.png");
	std::ifstream tile_info("config/tiles.config", std::ios::binary);
	if(tile_info.is_open()) {
		tile_info >> tile_count.x >> tile_count.y;
		tile_info >> tile_texture_size.x >> tile_texture_size.y;
		tile_info.close();
	}
	else {
		tile_count = {0, 0};
		tile_texture_size = {0, 0};
		SDL_Log("Could not find tiles.config...\n");
	}
	SDL_Log("Assets loaded\n");
}

Assets& Assets::get() noexcept {
	static Assets instance;
	return instance;
}