#include "sprite.hpp"

Sprite::Sprite(SDL_Texture *texture) noexcept : texture(texture), angle(0), origin(0, 0), flags(SDL_FLIP_NONE) {
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	sprite_rect  = {0, 0, w, h};
	texture_rect = {0, 0, w, h};
}

void Sprite::draw(SDL_Renderer *renderer, const Transform& transform) const noexcept {
	SDL_Rect draw_rect;
	draw_rect.x = sprite_rect.x + transform.translation.x;
	draw_rect.y = sprite_rect.y + transform.translation.y;
	draw_rect.w = sprite_rect.w;
	draw_rect.h = sprite_rect.h;
	// experimental
	//SDL_Point draw_origin = {origin.x + transform.translation.x, origin.y + transform.translation.y};
	//double draw_angle = angle + transform.angle;
	SDL_RenderCopyEx(renderer, texture, &texture_rect, &draw_rect, angle, &origin, flags);
}