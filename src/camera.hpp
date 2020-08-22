#pragma once

#include "transform.hpp"

class Camera {
public:

	constexpr Camera() noexcept {
		transform.translation = {0, 0};
	}

	constexpr void setPosition(float x, float y) {
		transform.translation = {x, y};
	}
	constexpr void setPosition(const glm::vec2& position) {
		transform.translation = position;
	}
	constexpr void move(float x, float y) noexcept {
		transform.translation.x += x;
		transform.translation.y += y;
	}
	constexpr void move(const glm::vec2& displacement) noexcept {
		transform.translation += displacement;
	}

	constexpr glm::vec2 pixelToCoords(const glm::vec2& point) const noexcept {
		return transform.translation + point;
	}

	constexpr glm::vec2 coordsToPixel(const glm::vec2& point) const noexcept {
		return point - transform.translation;
	}
	
	constexpr const Transform& getTransform() const noexcept { return transform; }

public:

	Transform transform;

};