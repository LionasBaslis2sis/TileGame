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
	const Input& input = Input::get();
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT: running = false; break; 
		}
	}
	Input::get().handleInput();
	// update camera
	float speed = 0.1;
	if(input.keyHeld(SDL_SCANCODE_A)) camera.move(-speed, 0);
	if(input.keyHeld(SDL_SCANCODE_D)) camera.move(speed, 0);
	if(input.keyHeld(SDL_SCANCODE_W)) camera.move(0, -speed);
	if(input.keyHeld(SDL_SCANCODE_S)) camera.move(0, speed);
	// edit the tile
	if(input.mouseButtonPressed(SDL_BUTTON_RIGHT)) {
		const glm::ivec2 pixel = camera.pixelToCoords(input.mousePosition());
		glm::ivec2 reduced = pixel / Tile::size;
		try {
			map.setTile(reduced, 1);
		} catch (const std::out_of_range& e) {
			SDL_Log("%s", e.what());
		}
	}
}

void Game::draw() const noexcept {
	SDL_RenderClear(renderer);
	RenderStates states;
	states.transform = -camera.getTransform();
	map.draw(renderer, states);
	player.draw(renderer, states);
    SDL_RenderPresent(renderer);
}