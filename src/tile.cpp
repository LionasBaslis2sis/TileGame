#include "tile.hpp"

Tile::Tile(int ID) noexcept : ID(ID) {
	sprite = Sprite(Assets::get().grass_tile);
	sprite.setSize(size, size);
}

void Tile::draw(SDL_Renderer* renderer, const Transform& transform) const noexcept {
	sprite.draw(renderer, transform);
}

void Tile::setID(int ID) noexcept {
	this->ID = ID;
}