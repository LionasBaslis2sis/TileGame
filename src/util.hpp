#pragma once

#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/vec2.hpp>
#include <glm/common.hpp>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path, glm::uvec2 * const size = NULL);

struct ray {
	constexpr ray() noexcept : origin(0, 0), dir(0, 0) {
		sign = {0, 0};
	}
	constexpr ray(const glm::vec2 &origin, const glm::vec2 &dir) noexcept : origin(origin), dir(dir) {
	glm::vec2 inv = 1.0f / dir;
	sign = {(inv.x < 0), ( inv.y < 0)};
	}
	glm::vec2 origin ;
	glm::vec2 dir;
	glm::ivec2 sign;

};

bool ray_vs_rect(const ray &ray, const SDL_Rect &rect, glm::vec2& contact_point, glm::vec2& contact_normal, float &t);

bool dynamic_rect_vs_rect(SDL_Rect& r_dynamic, glm::vec2& velocity, const float dt, const SDL_Rect& r_static, 
				glm::vec2& contact_point, glm::vec2& contact_normal, float& t) noexcept;

bool resolve_dynamic_rect_vs_rect(SDL_Rect& r_dynamic, glm::vec2& velocity, const float dt, const SDL_Rect& r_static) noexcept;