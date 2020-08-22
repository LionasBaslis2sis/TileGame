#pragma once

#include "transform.hpp"

struct RenderStates {
	SDL_Texture *texture = NULL;
	Transform transform;
};