#pragma once

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

	SDL_Texture *player, *grass_tile;

};