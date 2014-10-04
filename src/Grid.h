#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <memory>
#include "StaticSprite.h"
#include "StandardTexture.h"

class RenderManager;

using Position = std::pair<size_t, size_t>;

class Grid {
public:
	Grid(std::string& filename, size_t offsetX, size_t offsetY);

	void setTile(size_t xPos, size_t yPos, char value);
	size_t getWidth();
	size_t getHeight();
	bool tileIsBlocked(size_t xPos, size_t yPos);
	std::vector<Position> getAccessibleAdjacentTiles(Position pos);
	void Update();

private:
	size_t m_offsetX;
	size_t m_offsetY;
	size_t m_width;
	size_t m_height;
	std::vector<std::vector<char>> m_tiles;
	std::vector<std::vector<std::unique_ptr<StaticSprite<StandardTexture>>>> m_tileSprites;
};

#endif