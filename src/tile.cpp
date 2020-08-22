#include "tile.hpp"

Tile::Tile(int ID) noexcept : ID(ID) {
	sprite = Sprite(NULL);
	sprite.setSize(size, size);

}

void Tile::draw(SDL_Renderer* renderer, RenderStates states) const noexcept {
	sprite.draw(renderer, states);
}

void Tile::setID(int ID) noexcept {
	this->ID = ID;
	// change texture coordinates
	if(ID == -1) sprite.texture_rect = {0, 0, 0, 0};
	else {
		Uint32 count_x = Assets::get().tile_count.x;
		glm::uvec2 tex_size = Assets::get().tile_texture_size;
		glm::ivec2 position(ID % count_x, ID / count_x);
		sprite.texture_rect.x = tex_size.x * position.x;
		sprite.texture_rect.y = tex_size.y * position.y;
		sprite.texture_rect.w = tex_size.x;
		sprite.texture_rect.h = tex_size.y;
	}
}