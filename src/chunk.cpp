#include "chunk.hpp"

Chunk::~Chunk() {

} 

Chunk::Chunk() noexcept : render(false) {

}

Chunk::Chunk(int ID) noexcept : tiles(CHUNK_SIZE * CHUNK_SIZE, ID), render(true) {
	for(Uint32 i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		tiles[i].setPosition(Tile::size * indexToCoord(i));
	}
}

void Chunk::draw(SDL_Renderer *renderer) const noexcept {
	if(!render) return;
	for(auto& t : tiles) {
		t.draw(renderer);
	}
}

Tile& Chunk::getTile(int x, int y) {
	checkTile(x, y);
	return tiles[coordToIndex(x, y)];
}

Tile& Chunk::getTile(const glm::ivec2& position) {
	checkTile(position.x, position.y);
	return tiles[coordToIndex(position)];
}

void Chunk::setTile(int x, int y, int ID) {
	checkTile(x, y);
	tiles[coordToIndex(x, y)].setID(ID);
}

void Chunk::setTile(const glm::ivec2& position, int ID) {
	checkTile(position.x, position.y);
	tiles[coordToIndex(position)].setID(ID);
}