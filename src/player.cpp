#include "player.hpp"

Player::Player(const glm::ivec2& position) noexcept : position(position), velocity(0, 0) {
	sprite = Sprite(Assets::get().player_sheet);
	animation = Animation(sprite, {4, 1});
	sprite.setSize(size);
	loadSettings("config/player.config");
}

void Player::handleInput(float dt) noexcept {
	velocity = {0, 0};
	const Input& input = Input::get();
	if(input.keyHeld(SDL_SCANCODE_A)) velocity += glm::vec2{-speed * dt, 0};
	if(input.keyHeld(SDL_SCANCODE_D)) velocity += glm::vec2{speed * dt, 0};
	if(input.keyHeld(SDL_SCANCODE_W)) velocity += glm::vec2{0, -speed * dt};
	if(input.keyHeld(SDL_SCANCODE_S)) velocity += glm::vec2{0, speed * dt};	
}

void Player::handleCollisions(const Tilemap& map, float dt) noexcept {
	// get indices of tiles which are relevant in the collision detection
	// indices of the tile players' top left corner is overlaping
	float ts = Tile::size;
	glm::ivec2 reduced = position / ts;
	// indices of the tile players' future bottom right corner is overlaping
	glm::ivec2 next_reduced = glm::ceil((position + velocity * dt + size) / ts);
	// emplace indices in the procces vector
	std::vector<std::pair<glm::ivec2, float>> procces;
	if(reduced.y > next_reduced.y) std::swap(reduced.y, next_reduced.y);
	if(reduced.x > next_reduced.x) std::swap(reduced.x, next_reduced.x);
	glm::vec2 cp, cn;
	float t = 0;
	if(Input::get().mouseButtonPressed(SDL_BUTTON_LEFT)) 
		SDL_Log("x : [%i, %i], y : [%i, %i]", reduced.x, next_reduced.x, reduced.y, next_reduced.y);
	for(int y = reduced.y; y < next_reduced.y; y++) {
		for(int x = reduced.x; x < next_reduced.x; x++) {
			if(map.existsTile(x, y)) {
				Tile tile = map.getTile(x, y);;
				SDL_Rect& t_rect = tile.sprite.sprite_rect;
				SDL_Rect& p_rect = sprite.sprite_rect;
				if(tile.ID != 0 && dynamic_rect_vs_rect(p_rect, velocity, dt, t_rect, cp, cn, t)) {
					procces.emplace_back(glm::ivec2(x, y), t);
					SDL_Log("Collision");
				}
			}
		}
	}
	//-SDL_Log("Size: %i", (int)procces.size());
	// sort tiles 
	std::sort(procces.begin(), procces.end(), [](const std::pair<glm::ivec2, float>& a, const std::pair<glm::ivec2, float>& b){
		return a.second < b.second;
	});
	// resolve collisions
	for(auto& t : procces) {
		resolve_dynamic_rect_vs_rect(sprite.sprite_rect, velocity, dt, map.getTile(t.first).sprite.sprite_rect);
	}
}

void Player::update(const Tilemap& map, float dt) noexcept {
	handleInput(dt);
	animation.play(sprite, 0, 1000 * speed, dt);
	handleCollisions(map, dt);
	position += velocity * dt;
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