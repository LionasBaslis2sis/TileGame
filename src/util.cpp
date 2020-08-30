#include "util.hpp"

using namespace glm;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path, glm::uvec2 * const size) {
	if(!renderer) {
		SDL_Log("SDL_Renderer passed to SDL_Texture* loadFromFile(...) was nullptr\n");
		return nullptr;
	}
	SDL_Surface *surface = IMG_Load(path);
	if(!surface) {
		SDL_Log("SDL_Surface could not be loaded, error: %s", IMG_GetError());
		return nullptr;
	}
	if(size) *size = {surface->w, surface->h};
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture) {
		SDL_Log("SDL_Texture could not be created, error: %s", SDL_GetError());
		return nullptr;
	}
	SDL_FreeSurface(surface);
	return texture;
}

// I do not fully understand how it works, but let's hope it does
//https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/Videos/OneLoneCoder_PGE_Rectangles.cpp

bool ray_vs_rect(const ray &ray, const SDL_Rect &rect, 
			vec2& contact_point, vec2& contact_normal, float &t) {
	contact_point = {0, 0};
	contact_normal = {0, 0};
	vec2 invdir = 1.0f / ray.dir;
	vec2 pos = {rect.x, rect.y}, size = {rect.w, rect.h};
	vec2 t_near = vec2(pos - ray.origin) * invdir;
	vec2 t_far = (pos + size - ray.origin) * invdir;

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
	
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	t = std::max(t_near.x, t_near.y);

	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0) return false;

	contact_point = ray.origin + t * ray.dir;

	if (t_near.x > t_near.y) {
		if(invdir.x < 0) contact_normal = {1, 0};
		else contact_normal = {-1, 0};
	}
	else if (t_near.x < t_near.y) {
		if(invdir.y < 0) contact_normal = {0, 1};
		else contact_normal = {0, -1};
	}
	return true;
}

bool dynamic_rect_vs_rect(SDL_Rect& r_dynamic, vec2& velocity, const float dt, const SDL_Rect& r_static, 
				vec2& contact_point, vec2& contact_normal, float& t) noexcept {
	if (velocity.x == 0 && velocity.y == 0) return false;
	SDL_Rect expanded;
	expanded.x = r_static.x - r_dynamic.w/2;
	expanded.y = r_static.y - r_dynamic.h/2;
	expanded.w = r_static.w + r_dynamic.w;
	expanded.h = r_static.h + r_dynamic.h;
	ray r;
	r.origin.x = r_dynamic.x + r_dynamic.w/2;
	r.origin.y = r_dynamic.y + r_dynamic.h/2;
	r.dir = velocity * dt;
	if (ray_vs_rect(r, expanded, contact_point, contact_normal, t)) return (t >= 0.0f && t < 1.0f);
	return false;
}

bool resolve_dynamic_rect_vs_rect(SDL_Rect& r_dynamic, vec2& velocity, const float dt, const SDL_Rect& r_static) noexcept {
	vec2 cp, cn;
	float t = 0;
	if (dynamic_rect_vs_rect(r_dynamic, velocity, dt, r_static, cp, cn, t)) {
		velocity += cn * glm::abs(velocity) * (1 - t);
		return true;
	}
	return false;
}