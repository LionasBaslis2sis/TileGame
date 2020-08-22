#pragma once

#include "sprite.hpp"
#include "assets.hpp"

class Tile {
public:
	constexpr Tile() noexcept { setID(-1); }

	Tile(int ID) noexcept;

	void draw(SDL_Renderer* renderer, RenderStates states) const noexcept;

	void setID(int ID) noexcept;

	constexpr void setPosition(int x, int y) noexcept {
		sprite.setPosition(x, y);
	}

	constexpr void setPosition(const glm::ivec2& position) noexcept {
		sprite.setPosition(position);
	}

	int ID;
	// this is bad, all the chunk tiles 
	// should be rendered in one draw call
	// and individual tiles should not hold a sprite obj
	Sprite sprite;

	// default size of tiles
	static constexpr int size = 32;
};