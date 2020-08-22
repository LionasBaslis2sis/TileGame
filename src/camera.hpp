#pragma once

#include "transform.hpp"

class Camera {
public:

	constexpr Camera() noexcept {
		transform.translation = {0, 0};
	}

	constexpr void setPosition(int x, int y) {
		transform.translation = {x, y};
	}
	constexpr void setPosition(const glm::ivec2& position) {
		transform.translation = position;
	}
	constexpr void translate(int x, int y) noexcept {
		transform.translation.x += x;
		transform.translation.y += y;
	}
	constexpr void translate(const glm::ivec2& displacement) noexcept {
		transform.translation += displacement;
	}
	
	constexpr const Transform& getTransform() const noexcept { return transform; }

public:
	Transform transform;

};