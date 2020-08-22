#include "sprite.hpp"

Sprite::Sprite(SDL_Texture *texture) noexcept : texture(texture), angle(0), origin(0, 0), flags(SDL_FLIP_NONE) {
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	sprite_rect  = {0, 0, w, h};
	texture_rect = {0, 0, w, h};
}

void Sprite::draw(SDL_Renderer *renderer, RenderStates states) const noexcept {
	SDL_Rect draw_rect = sprite_rect;
	draw_rect.x += states.transform.translation.x;
	draw_rect.y += states.transform.translation.y;
	SDL_RenderCopyEx(renderer, states.texture ? states.texture : texture, &texture_rect, &draw_rect, angle, &origin, flags);
}