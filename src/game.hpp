#pragma once

#include <cstdio> // printf

#include "util.hpp"
#include "assets.hpp"
#include "sprite.hpp"

class Game {

public:

	~Game();
	constexpr Game() noexcept : window(nullptr), renderer(nullptr), running(false) { }
	Game(const char* title, Uint32 x, Uint32 y, Uint32 w, Uint32 h) noexcept;
	
	void run(float dt) noexcept;
	void update(float dt) noexcept;
	void draw() const noexcept;

public:

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;

	Sprite player, grass_tile;

};