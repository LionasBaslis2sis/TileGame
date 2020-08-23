#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "sprite.hpp"

class Animation {
public:
	constexpr Animation() noexcept : sprite(NULL) { }
	Animation(Sprite& sprite, const glm::ivec2& sprite_count) noexcept;
	
	constexpr void setFrame(Uint32 x, Uint32 y) noexcept {
		if(sprite) {
			SDL_Rect texture_rect;
			texture_rect.x = x * sprite_size.x;
			texture_rect.y = y * sprite_size.y;
			texture_rect.w = sprite_size.x;
			texture_rect.h = sprite_size.y;
			sprite->texture_rect = texture_rect;
		}
	}

	void play(Sprite& spr, Uint32 row, Uint32 frame_time, Uint32 dt) noexcept {
		frame_lifetime += dt;
		if((frame_lifetime >= frame_time) && sprite) {
			spr.texture_rect.y = row * sprite_size.y;
			spr.texture_rect.x += sprite_size.x;
			if(spr.texture_rect.x == sheet_size.x) spr.texture_rect.x = 0;
			frame_lifetime = 0;
		}
	}

public:
	// dimensions of 1 sprite in the texture sheet
	glm::ivec2 sprite_size;
	glm::ivec2 sheet_size;
	glm::ivec2 sprite_count;
	// lifetime of the current frame in milliseconds
	Uint32 frame_lifetime;
};