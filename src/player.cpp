#include "player.hpp"

Player::Player(const glm::ivec2& position) noexcept : position(position), velocity(0, 0) {
	sprite = Sprite(Assets::get().player);
	sprite.setSize(size);
	loadSettings("config/player.config");
}

void Player::handleInput(float dt) noexcept {
	const Input& input = Input::get();
	if(input.keyHeld(SDL_SCANCODE_A)) velocity += glm::vec2{-speed * dt, 0};
	if(input.keyHeld(SDL_SCANCODE_D)) velocity += glm::vec2{speed * dt, 0};
	if(input.keyHeld(SDL_SCANCODE_W)) velocity += glm::vec2{0, -speed * dt};
	if(input.keyHeld(SDL_SCANCODE_S)) velocity += glm::vec2{0, speed * dt};
	position += velocity;
	velocity = {0, 0};
}

void Player::handleCollisions(const Tilemap& map) noexcept {
	// will implement this later
}

void Player::update(const Tilemap& map, float dt) noexcept {
	handleInput(dt);
	handleCollisions(map);
	sprite.setPosition(position);
}

void Player::draw(SDL_Renderer* renderer, RenderStates states) const noexcept {
	sprite.draw(renderer, states);
}

void Player::loadSettings(const char* path) noexcept {
	std::ifstream settings(path);
	if(!settings.is_open()) {
		SDL_Log("Could not load player settings from %s", path);
	}
	else {
		settings >> speed;
		settings.close();
		SDL_Log("Player settings loaded");
	}
}