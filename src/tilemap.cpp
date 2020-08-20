#include "tilemap.hpp"

Tilemap::~Tilemap(){
	
}

Tilemap::Tilemap() noexcept : size(0, 0) {

}

Tilemap::Tilemap(Uint32 width, Uint32 height, int ID) noexcept : chunks(width * height, ID) {
	size = glm::uvec2(width, height);
	for(Uint32 i = 0; i < size.x * size.y; i++) {
		chunks[i].setPosition(CHUNK_SIZE * Tile::size * indexToCoord(i));
	}
}

void Tilemap::draw(SDL_Renderer *renderer, const Transform& transform) const noexcept {
	for(auto& c : chunks) c.draw(renderer, transform);
}

void Tilemap::setTile(Uint32 x, Uint32 y, int ID) {
	// get local chunk coords
	Uint32 local_x = x % CHUNK_SIZE;
	Uint32 local_y = y % CHUNK_SIZE;
	// get chunk coordinates
	Uint32 chunk_x = (x - local_x) / CHUNK_SIZE;
	Uint32 chunk_y = (y - local_y) / CHUNK_SIZE;
	if(!exists(chunk_x, chunk_y)) {
		std::stringstream message;
		message << "Chunk at (" << x << ", " << y << ") does not exist\n";
		throw std::out_of_range(message.str());
	}
	chunks[coordToIndex(chunk_x, chunk_y)].setTile(local_x, local_y, ID);
}

void Tilemap::setTile(const glm::ivec2& position, int ID) {
	setTile(position.x, position.y, ID);
}


Tile& Tilemap::getTile(Uint32 x, Uint32 y) {
	// get local chunk coords
	Uint32 local_x = x % CHUNK_SIZE;
	Uint32 local_y = y % CHUNK_SIZE;
	// get chunk coordinates
	Uint32 chunk_x = (x - local_x) / CHUNK_SIZE;
	Uint32 chunk_y = (y - local_y) / CHUNK_SIZE;
	if(!exists(chunk_x, chunk_y)) {
		std::stringstream message;
		message << "Chunk at (" << x << ", " << y << ") does not exist\n";
		throw std::out_of_range(message.str());
	}
	return chunks[coordToIndex(chunk_x, chunk_y)].getTile(local_x, local_y);
}

Tile& Tilemap::getTile(const glm::ivec2& position) {
	return getTile(position.x, position.y);
}


Tile Tilemap::getTile(Uint32 x, Uint32 y) const {
	return getTile(x, y);
}

Tile Tilemap::getTile(const glm::ivec2& position) const {
	return getTile(position.x, position.y);
}


Uint32 Tilemap::coordToIndex(Uint32 x, Uint32 y) const noexcept {
	return x + y * size.x;
}

Uint32 Tilemap::coordToIndex(const glm::ivec2& position) const noexcept {
	return position.x + position.y * size.x;
}


glm::ivec2 Tilemap::indexToCoord(Uint32 index) const noexcept {
	return glm::ivec2(index % size.x, index / size.x);
}


bool Tilemap::exists(Uint32 x, Uint32 y) const noexcept {
	return (x < size.x && y < size.y);
}

bool Tilemap::exists(const glm::uvec2& position) const noexcept {
	return (position.x < size.x && position.y < size.y);
}
