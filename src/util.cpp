#include "util.hpp"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path, Uint32 *w, Uint32 *h) {
	if(!renderer) {
		SDL_Log("SDL_Renderer passed to SDL_Texture* loadFromFile(...) was nullptr\n");
		return nullptr;
	}
	SDL_Surface *surface = IMG_Load(path);
	if(!surface) {
		SDL_Log("SDL_Surface could not be loaded, error: %s", IMG_GetError());
		return nullptr;
	}
	if(w) *w = surface->w;
	if(h) *h = surface->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture) {
		SDL_Log("SDL_Texture could not be created, error: %s", SDL_GetError());
		return nullptr;
	}
	SDL_FreeSurface(surface);
	return texture;
}