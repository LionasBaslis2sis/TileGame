#pragma once

#include <cstdio> // printf

#include "util.hpp"
#include "assets.hpp"

class Game {

public:

	~Game();
	Game();
	Game(const char* title, Uint32 x, Uint32 y, Uint32 w, Uint32 h) noexcept;
	
	void run(float dt) noexcept;
	void update(float dt) noexcept;
	void draw() noexcept;

public:

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;

	SDL_Rect player_dest;

};