#pragma once

#include <cstdio> // printf

#include "util.hpp"
#include "assets.hpp"
#include "sprite.hpp"
#include "chunk.hpp"

class Game {

public:

	~Game();
	Game() noexcept;
	Game(const char* title, Uint32 x, Uint32 y, Uint32 w, Uint32 h) noexcept;
	
	void run(float dt) noexcept;
	void update(float dt) noexcept;
	void draw() const noexcept;

public:

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;

	Sprite player;
	Chunk chunk;

};