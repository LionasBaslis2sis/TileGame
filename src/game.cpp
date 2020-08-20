#include "game.hpp"

Game::~Game() {
	Assets::get().cleanup();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Log("Game destructed\n");
}

Game::Game() noexcept : window(nullptr), renderer(nullptr), running(false) { 

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
	// game objects
	player = Sprite(Assets::get().player);
	player.setSize(64, 64);

	map = Tilemap(2, 2, 0);
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
		switch(event.type) {
			case SDL_QUIT: running = false; break; 
		}
	}
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if(keys[SDLK_a]) player.move(-1, 0);
	if(keys[SDLK_d]) player.move(1, 0);
	if(keys[SDLK_w]) player.move(0, -1);
	if(keys[SDLK_s]) player.move(0, 1);
}

void Game::draw() const noexcept {
	SDL_RenderClear(renderer);
	map.draw(renderer, camera.getTransform());
	player.draw(renderer, camera.getTransform());
    SDL_RenderPresent(renderer);
}