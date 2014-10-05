#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <memory>
#include "StaticSprite.h"
#include "StandardTexture.h"
#include <chrono>


class RenderManager;
class Entity;
class Dijkstra;

class Grid {
	using Position = std::pair<size_t, size_t>;

public:
	Grid(std::string& filename, size_t offsetX, size_t offsetY);

	void setTile(size_t xPos, size_t yPos, char value);
	size_t getWidth();
	size_t getHeight();
	bool tileIsBlocked(size_t xPos, size_t yPos);
	std::vector<Position> getAccessibleAdjacentTiles(Position pos);	
	void Update();
	std::vector<std::shared_ptr<Entity>> getEntitiesInRange(std::shared_ptr<Entity> entity);

private:
	Dijkstra* m_dijkstraAlgorithm;

	size_t m_offsetX;
	size_t m_offsetY;
	size_t m_width;
	size_t m_height;
	int distance(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	std::vector<std::vector<char>> m_tiles;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::vector<std::unique_ptr<StaticSprite<StandardTexture>>>> m_tileSprites;
	//std::chrono::system_clock::time_point m_roundStartTimePoint;
	std::chrono::system_clock::time_point m_lastSpawnTimePoint;
	std::chrono::system_clock::time_point m_lastUpdateTimePoint;
};

#endif