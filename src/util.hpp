#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path, Uint32 *w = nullptr, Uint32 *h = nullptr);