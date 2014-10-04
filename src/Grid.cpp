#include "Grid.h"
#include <iostream>

Grid::Grid(size_t width, size_t height) {
	this->width = width;
	this->height = height;

	for (size_t i = 0; i < width; ++i) {
		std::vector<char> tempVec;
		for (size_t j = 0; j < height; j++)
		{
			tempVec.push_back('.');
		}
		this->tiles.push_back(tempVec);
	}
}



void Grid::setTile(size_t xPos, size_t yPos, char value) {
	this->tiles[xPos][yPos] = value;
}

size_t Grid::getWidth() {
	return this->width;
}

size_t Grid::getHeight() {
	return this->height;
}

bool Grid::tileIsBlocked(size_t xPos, size_t yPos) {
	//TODO!

	return this->tiles[xPos][yPos] != '.';
}

std::vector<std::pair<size_t, size_t>> Grid::getAccessibleAdjacentTiles(std::pair<size_t, size_t> pos) {
	std::vector<std::pair<size_t, size_t>> retVec;

	if (pos.first > 0						&& !this->tileIsBlocked(pos.first - 1, pos.second)) retVec.emplace_back(pos.first - 1, pos.second);
	if (pos.second > 0						&& !this->tileIsBlocked(pos.first, pos.second - 1)) retVec.emplace_back(pos.first, pos.second - 1);
	if (pos.first + 1 < this->getWidth()	&& !this->tileIsBlocked(pos.first + 1, pos.second)) retVec.emplace_back(pos.first + 1, pos.second);
	if (pos.second + 1 < this->getHeight()	&& !this->tileIsBlocked(pos.first, pos.second + 1)) retVec.emplace_back(pos.first, pos.second + 1);

	return retVec;
}

void Grid::show() {
	//std::system("cls");

	for (size_t i = 0; i < this->getWidth(); i++)
	{
		for (size_t j = 0; j < this->getHeight(); j++)
		{
			std::cout << this->tiles[i][j];
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}
