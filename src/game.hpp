#pragma once

#include <cstdio> // printf

#include "util.hpp"
#include "assets.hpp"
#include "camera.hpp"
#include "tilemap.hpp"
#include "player.hpp"
#include "input.hpp"

class Game {

public:

	~Game();
	Game() noexcept;
	Game(const char* title, Uint32 x, Uint32 y, Uint32 w, Uint32 h) noexcept;

	void update(float dt) noexcept;
	void draw() const noexcept;

public:

	SDL_Window *window;
	glm::ivec2 window_size;
	SDL_Renderer *renderer;
	bool running;

	Player player;
	Camera camera;
	Tilemap map;
};