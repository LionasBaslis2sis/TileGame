#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <cstring>

class Input {
private:

	constexpr Input() noexcept {
		memset(last_keys, 0, SDL_NUM_SCANCODES);
		memset(current_keys, 0, SDL_NUM_SCANCODES);
		last_mouse_mask = 0;
		current_mouse_mask = 0;
		mouse = glm::ivec2(0, 0);
	}


public:

	// this should be called outside the SDL_PollEvent loop
	void handleInput() noexcept {
		memcpy(last_keys, current_keys, SDL_NUM_SCANCODES);
		// keyboard
		int keynum;
		const Uint8 *temp = SDL_GetKeyboardState(&keynum);
		memcpy(current_keys, temp, keynum);
		// mouse
		last_mouse_mask = current_mouse_mask;
		current_mouse_mask = SDL_GetMouseState(&mouse.x, &mouse.y);
	}

	// keyboard access

	constexpr bool keyHeld(const Uint32 key) const noexcept {
		return key >= SDL_NUM_SCANCODES? false : current_keys[key];
	}

	constexpr bool keyPressed(const Uint32 key) const noexcept {
		const bool last_state    = key >= SDL_NUM_SCANCODES? false :    last_keys[key];
		const bool current_state = key >= SDL_NUM_SCANCODES? false : current_keys[key];
		return (!last_state && current_state);
	}

	constexpr bool keyReleased(const Uint32 key) const noexcept {
		const bool last_state    = key >= SDL_NUM_SCANCODES? false :    last_keys[key];
		const bool current_state = key >= SDL_NUM_SCANCODES? false : current_keys[key];
		return (last_state && !current_state);
	}
	
	// mouse access

	constexpr glm::ivec2 mousePosition() const noexcept {
		return mouse;
	}

	constexpr bool mouseButtonHeld(const Uint32 mouse_button) const noexcept {
		return current_mouse_mask & SDL_BUTTON(mouse_button);
	}

	constexpr bool mouseButtonPressed(const Uint32 mouse_button) const noexcept {
		const bool last_state    = last_mouse_mask    & SDL_BUTTON(mouse_button);
		const bool current_state = current_mouse_mask & SDL_BUTTON(mouse_button); 
		return (!last_state && current_state);	
	}

	constexpr bool mouseButtonReleased(const Uint32 mouse_button) const noexcept {
		const bool last_state    = last_mouse_mask    & SDL_BUTTON(mouse_button);
		const bool current_state = current_mouse_mask & SDL_BUTTON(mouse_button); 
		return (last_state && !current_state);	
	}

	static Input& get() noexcept {
		static Input instance;
		return instance;
	}

public:
	/// keyboard
	// key info of the current frame
	Uint8 current_keys[SDL_NUM_SCANCODES];
	// key info of the last frame
	Uint8 last_keys[SDL_NUM_SCANCODES];
	/// mouse
	// bit mask of the current frame returned by SDL_GetMouseState
	Uint32 current_mouse_mask;
	// bit mask of the last frame returned by SDL_GetMouseState
	Uint32 last_mouse_mask;
	// position of the mouse
	glm::ivec2 mouse;

};