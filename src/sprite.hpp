#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

#include "transform.hpp"

class Sprite {

public:

	constexpr Sprite() noexcept : texture(nullptr), angle(0), origin(0, 0), flags(SDL_FLIP_NONE) {
		sprite_rect  = {0, 0, 0, 0};
		texture_rect = {0, 0, 0, 0};
	}

	Sprite(SDL_Texture *texture) noexcept;

	void draw(SDL_Renderer *renderer, const Transform& transform) const noexcept;

	constexpr void setRect(int x, int y, int w, int h) noexcept {
		sprite_rect = {x, y, w, h};
		this->x = x; this->y = y;
		this->w = w; this->h =  h;
	}

	constexpr void setPosition(int x, int y) noexcept {
		sprite_rect.x = x; this->x = x;
		sprite_rect.y = y; this->y = y;
	}

	constexpr void setPosition(const glm::ivec2& position) noexcept {
		sprite_rect.x = position.x; this->x = position.x;
		sprite_rect.y = position.y; this->y = position.y;
	}

	constexpr void move(int x, int y) noexcept {
		sprite_rect.x += x; this->x += x;
		sprite_rect.y += y; this->y += y;
	}

	constexpr void move(const glm::ivec2& position) noexcept {
		sprite_rect.x += position.x; this->x += position.x;
		sprite_rect.y += position.y; this->y += position.y;
	}

	constexpr void setSize(int w, int h) noexcept {
		sprite_rect.w = w; this->w = w;
		sprite_rect.h = h; this->h=  h;
	}
	
	constexpr void setSize(const glm::ivec2& size) noexcept {
		sprite_rect.w = size.x; this->w = size.x;
		sprite_rect.h = size.y; this->h=  size.y;
	}

	constexpr void setTextureRect(int x, int y, int w, int h) noexcept {
		texture_rect = {x, y, w, h};
	}

	constexpr void setTexture(SDL_Texture* texture) noexcept {
		this->texture = texture;
	}

	constexpr void setRotation(float angle) noexcept {
		this->angle = angle;
	}

	constexpr void rotate(float angle) noexcept {
		this->angle += angle;
	}

	constexpr void setOrigin(int x, int y) noexcept {
		origin = {x, y};
	}

	constexpr void setOrigin(SDL_Point origin) noexcept {
		this->origin = origin;
	}

	constexpr void setOrigin(const glm::ivec2& origin) noexcept {
		this->origin = {origin.x, origin.y};
	}

	constexpr void setRendererFlipFlags(SDL_RendererFlip flags) noexcept {
		this-> flags = flags;
	}

	constexpr void resetRendererFlipFlags() noexcept {
		this->flags = SDL_FLIP_NONE;
	}

public:

	SDL_Texture *texture;
	SDL_Rect sprite_rect; 
	SDL_Rect texture_rect;
	float angle;
	SDL_Point origin;
	SDL_RendererFlip flags;
	// sprite.x instead of sprite.sprite_rect.x ect...
	// chaning them does not affect the rendered sprite
	int x, y, w, h;
};