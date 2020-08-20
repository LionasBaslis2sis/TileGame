#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/vec2.hpp>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path, Uint32 *w = nullptr, Uint32 *h = nullptr);