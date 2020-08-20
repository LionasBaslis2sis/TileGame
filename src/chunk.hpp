#pragma once

#include <sstream>
#include <vector>

#include "util.hpp"
#include "tile.hpp"

#define CHUNK_SIZE 8

class Chunk {

public:
	~Chunk();
	Chunk() noexcept;
	Chunk(int ID) noexcept;
	Chunk(int x, int y, int ID) noexcept;
	Chunk(glm::ivec2& position, int ID) noexcept;

	void draw(SDL_Renderer *renderer, const Transform& transform) const noexcept;

	Tile& getTile(int x, int y);
	Tile& getTile(const glm::ivec2& position);

	void setTile(int x, int y, int ID);
	void setTile(const glm::ivec2& position, int ID);

	constexpr int coordToIndex(int x, int y) const noexcept { 
		return x + y * CHUNK_SIZE; 
	}
	constexpr int coordToIndex(const glm::ivec2& position) const noexcept { 
		return position.x + position.y * CHUNK_SIZE; 
	}
	constexpr glm::ivec2 indexToCoord(int index) const noexcept { 
		return glm::ivec2(index % CHUNK_SIZE, index / CHUNK_SIZE);
	}

	constexpr bool exists(int index) const noexcept {
		return (index >= 0 && index < CHUNK_SIZE * CHUNK_SIZE);
	}
	constexpr bool exists(int x, int y) const noexcept {
		return (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE);
	}
	constexpr bool exists(const glm::ivec2& position) const noexcept {
		return (position.x >= 0 && position.x < CHUNK_SIZE && 
				position.y >= 0 && position.y < CHUNK_SIZE);
	}

	constexpr void setPosition(int x, int y) noexcept {
		for(Uint32 i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
			tiles[i].setPosition(glm::ivec2(x, y) + Tile::size * indexToCoord(i));
		}
	}
	constexpr void setPosition(const glm::ivec2& position) noexcept {
		for(Uint32 i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
			tiles[i].setPosition(position + Tile::size * indexToCoord(i));
		}	
	}

private:

	void checkTile(int x, int y) const {
		if(!exists(x, y)) {
			std::stringstream message;
			message << "Tile at (" << x << ", " << y << ") does not exist.\n";
			throw std::out_of_range(message.str());
		}
	}

public: 
	std::vector<Tile> tiles;
	bool render;
};