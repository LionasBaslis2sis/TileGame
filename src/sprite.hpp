#pragma once

#include <SDL2/SDL.h>

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

	constexpr void setTextureRect(int x, int y, int w, int h) noexcept {
		texture_rect = {x, y, w, h};
	}

public:

	SDL_Texture *texture;
	SDL_Rect sprite_rect; 
	SDL_Rect texture_rect;
	// sprite.x instead of sprite.sprite_rect.x ect...
	// chaning them does not affect the rendered sprite
	int x, y, w, h;
};