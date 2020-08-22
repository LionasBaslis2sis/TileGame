#pragma once

#include "chunk.hpp"

class Tilemap {
public:

	~Tilemap();
	Tilemap() noexcept;
	Tilemap(Uint32 width, Uint32 height, int ID) noexcept;

	void draw(SDL_Renderer *renderer, RenderStates states) const noexcept;

	void setTile(Uint32 x, Uint32 y, int ID);
	void setTile(const glm::ivec2& position, int ID);
	
	Tile& getTile(Uint32 x, Uint32 y);
	Tile& getTile(const glm::ivec2& position);

	Tile getTile(Uint32 x, Uint32 y) const;
	Tile getTile(const glm::ivec2& position) const;

	Uint32 coordToIndex(Uint32 x, Uint32 y) const noexcept;
	Uint32 coordToIndex(const glm::ivec2& position) const noexcept;

	glm::ivec2 indexToCoord(Uint32 index) const noexcept;

	bool exists(Uint32 x, Uint32 y) const noexcept;
	bool exists(const glm::uvec2& position) const noexcept;

public:
	std::vector<Chunk> chunks;
	glm::uvec2 size;
};