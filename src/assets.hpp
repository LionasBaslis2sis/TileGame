#pragma once

#include <glm/vec2.hpp>
#include <fstream>
#include "util.hpp"

class Assets {

private:
	constexpr Assets() noexcept :
	player(nullptr) { }

public:

	~Assets();
	void cleanup() noexcept;
	void init(SDL_Renderer *renderer) noexcept;
	static Assets& get() noexcept;

	Assets(Assets const&) = delete;
    void operator=(Assets const&) = delete;

public:

	SDL_Texture *player, *tiles, *player_sheet;
	// tile_texture_size - size of the individual 
	// tiles in pixels of the texture
	glm::uvec2 tile_count, tile_texture_size;

};