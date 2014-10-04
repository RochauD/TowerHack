#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
	using Position = std::pair<size_t, size_t>;

private:
	size_t width;
	size_t height;
	std::vector<std::vector<char>> tiles;

public:

	Grid(size_t width, size_t height);

	void setTile(size_t xPos, size_t yPos, char value);

	size_t getWidth();
	size_t getHeight();
	bool tileIsBlocked(size_t xPos, size_t yPos);
	std::vector<Position> getAccessibleAdjacentTiles(Position pos);
	void show();
};

#endif