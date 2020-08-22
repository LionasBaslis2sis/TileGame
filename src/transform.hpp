#pragma once
#include <glm/vec2.hpp>

struct Transform {

	constexpr Transform() noexcept : translation(0, 0) { }

	constexpr Transform operator - () const noexcept {
		Transform result;
		result.translation = -translation;
		return result;
	}

	glm::vec2 translation;
};