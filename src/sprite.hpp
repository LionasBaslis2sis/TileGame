#pragma once

#include <SDL2/SDL.h>
#include "vec2.hpp"
#include "mat3.hpp"

class Sprite {

public:

	constexpr Sprite() noexcept : texture(nullptr) {
		sprite_rect  = {0, 0, 0, 0};
		texture_rect = {0, 0, 0, 0};
	}

	Sprite(SDL_Texture *texture) noexcept;

	void draw(SDL_Renderer *renderer) const noexcept;

	constexpr void setRect(int x, int y, int w, int h) noexcept {
		sprite_rect = {x, y, w, h};
		this->x = x;
		this->y = y;
		this->w = w;
		this->h =  h;
	}

	constexpr void setPosition(int x, int y) noexcept {
		sprite_rect.x = x;
		sprite_rect.y = y;
		this->x = x;
		this->y = y;
	}

	constexpr void setSize(int w, int h) noexcept {
		sprite_rect.w = w;
		sprite_rect.h = h;
		this->w = w;
		this->h=  h;
	}

	constexpr void setPosition(const vec2i& position) noexcept {
		sprite_rect.x = position.x;
		sprite_rect.y = position.y;
		this->x = position.x;
		this->y = position.y;
	}

	constexpr void setSize(const vec2i& size) noexcept {
		sprite_rect.w = size.x;
		sprite_rect.h = size.y;
		this->w = size.x;
		this->h=  size.y;
	}

	constexpr void setTextureRect(int x, int y, int w, int h) noexcept {
		texture_rect = {x, y, w, h};
	}

	constexpr void setTexture(SDL_Texture* texture) noexcept {
		this->texture = texture;
	}

public:

	SDL_Texture *texture;
	SDL_Rect sprite_rect; 
	SDL_Rect texture_rect;
	// sprite.x instead of sprite.sprite_rect.x ect...
	// chaning them does not affect the rendered sprite
	int x, y, w, h;
};