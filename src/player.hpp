#pragma once

#include <fstream>
#include "input.hpp"
#include "assets.hpp"
#include "sprite.hpp"
#include "tilemap.hpp"
#include "animation.hpp"

class Player {
public:
	constexpr Player() noexcept { }
	Player(const glm::ivec2& position) noexcept;

	void handleInput(float dt) noexcept;
	void handleCollisions(const Tilemap& map, float dt) noexcept;
	void update(const Tilemap& map, float dt) noexcept;

	void draw(SDL_Renderer* renderer, RenderStates states) const noexcept;

	void loadSettings(const char* path) noexcept;

public:
	static constexpr glm::vec2 size = glm::vec2(48, 48);
	glm::vec2 position, velocity;
	float speed;
	Sprite sprite;
	Animation animation;
};