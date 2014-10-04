#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <utility>
#include <set>
#include <algorithm>
#include "Grid.h"

class Dijkstra {
	using Position = std::pair<size_t, size_t>;
	using ValPosition = std::pair<Position, int>;

private:
	Grid* grid;
	std::vector<std::vector<size_t>> distance;
	std::vector<std::vector<Position>> parent;
	std::vector<std::vector<bool>> scanned;
	std::set<Position> gridNodes;

	size_t getDistance(ValPosition vPos);
	size_t getDistance(Position vPos);
	void setDistance(ValPosition vPos, size_t dist);
	void setDistance(Position vPos, size_t dist);
	void setParent(Position pos, ValPosition vPos);

public:
	Dijkstra(Grid &grid);
	void removeGridNode(size_t xPos, size_t yPos);
	Position getNextMove(Position currPos);
	Position getNextMove(size_t xPos, size_t yPos);
	void calculateInitialPaths(Position end);
};

#endif