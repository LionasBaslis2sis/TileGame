#pragma once

#include "sprite.hpp"
#include "assets.hpp"

class Tile {
public:
	constexpr Tile() noexcept : ID(-1) { }

	Tile(int ID) noexcept;

	void draw(SDL_Renderer* renderer, const Transform& transform) const noexcept;

	void setID(int ID) noexcept;

	constexpr void setPosition(int x, int y) noexcept {
		sprite.setPosition(x, y);
	}

	constexpr void setPosition(const glm::ivec2& position) noexcept {
		sprite.setPosition(position);
	}

	int ID;
	// this is bad, all the tile sprites should be stored
	// in chunks to increase the performace
	Sprite sprite;

	// default size of tiles
	static constexpr int size = 32;
};