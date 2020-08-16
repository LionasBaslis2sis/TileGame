#include "sprite.hpp"

Sprite::Sprite(SDL_Texture *texture) noexcept : texture(texture) {
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	sprite_rect  = {0, 0, w, h};
	texture_rect = {0, 0, w, h};
}

void Sprite::draw(SDL_Renderer *renderer) const noexcept {
	SDL_RenderCopy(renderer, texture, &texture_rect, &sprite_rect);
}