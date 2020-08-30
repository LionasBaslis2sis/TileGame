#include "animation.hpp"

Animation::Animation(Sprite& sprite, const glm::ivec2& sprite_count) noexcept : 
sheet_size(sprite.w, sprite.h), sprite_count(sprite_count) {
	sprite_size = sheet_size / sprite_count;
	sprite.texture_rect = {0, 0, sprite_size.x, sprite_size.y};
}