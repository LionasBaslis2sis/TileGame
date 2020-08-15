#pragma once

#include "util.hpp"

class Assets {

private:

	~Assets();
	constexpr Assets() noexcept;

public:

	void init(SDL_Renderer* renderer) noexcept;
	static Assets& get() noexcept;

	Assets(Assets const&) = delete;
    void operator=(Assets const&) = delete;

public:

	SDL_Texture* player;

};