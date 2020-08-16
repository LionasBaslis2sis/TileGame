#include "game.hpp"

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

Game::Game(const char* title, Uint32 x, Uint32 y, Uint32 w, Uint32 h) noexcept {
	// setup SDL_Window & SDL_Renderer
	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL);
	if(!window) {
		SDL_Log("Failed to create SDL_Window, error: %s", SDL_GetError());
	}
	running = true;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		SDL_Log("Failed to create SDL_Renderer, error: %s", SDL_GetError());
	}
	// call init functions
	Assets::get().init(renderer);
	player = Sprite(Assets::get().player);
	player.setSize(64, 64);
}

void Game::run(float dt) noexcept {
	while(running) {
		this->update(dt);
		this->draw();
	}
}

void Game::update(float dt) noexcept {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) running = false;
	}
}

void Game::draw() const noexcept {
	SDL_RenderClear(renderer);
	player.draw(renderer);
    SDL_RenderPresent(renderer);
}