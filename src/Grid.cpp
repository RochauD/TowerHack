#include "Grid.h"
#include <fstream>
#include "Renderable.h"

Grid::Grid(std::string& filename, size_t offsetX, size_t offsetY)
{
	this->m_offsetX = offsetX;
	this->m_offsetY = offsetY;
	std::ifstream file(filename);
	if (file.is_open())
	{
		file >> this->m_width;
		file >> this->m_height;
	}

	char buffer;
	// add error checking 

	this->m_tiles.resize(this->m_height);
	for (size_t i = 0; i < this->m_height; ++i)
	{
		this->m_tiles[i].resize(this->m_width);
	}

	for (size_t i = 0; i < this->m_height; ++i)
	{
		for (size_t j = 0; j < this->m_width; j++)
		{
			file >> buffer;
			this->m_tiles[i][j] = buffer;
		}
	}


	this->m_tileSprites.resize(this->m_height);
	for (size_t i = 0; i < this->m_height; ++i)
	{
		this->m_tileSprites[i].resize(this->m_width);
	}

	for (size_t i = 0; i < this->m_height; ++i)
	{
		for (size_t j = 0; j < this->m_width; ++j)
		{
			if (this->m_tiles[i][j] == 'x')
			{
				this->m_tileSprites[i][j] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
				StandardTexture* temp = this->m_tileSprites[i][j]->GetTexture();
				temp->LoadTexture("wall.png");
				this->m_tileSprites[i][j]->SetZIndex(10000);
				this->m_tileSprites[i][j]->SetVisibilityFlag(false);
				this->m_tileSprites[i][j]->Show(true);
				this->m_tileSprites[i][j]->UpdatePositions();
				this->m_tileSprites[i][j]->UpdateTexCoords();
				this->m_tileSprites[i][j]->setPosition(this->m_offsetX + 20 * j, this->m_offsetY + 20 * i);
			}
			else if (this->m_tiles[i][j] == '_')
			{
				this->m_tileSprites[i][j] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
				StandardTexture* temp = this->m_tileSprites[i][j]->GetTexture();
				temp->LoadTexture("greenTile.png");
				this->m_tileSprites[i][j]->SetZIndex(10000);
				this->m_tileSprites[i][j]->SetVisibilityFlag(false);
				this->m_tileSprites[i][j]->Show(true);
				this->m_tileSprites[i][j]->UpdatePositions();
				this->m_tileSprites[i][j]->UpdateTexCoords();
				this->m_tileSprites[i][j]->setPosition(this->m_offsetX + 20 * j, this->m_offsetY + 20 * i);
			}
		}
	}
}


void Grid::setTile(size_t xPos, size_t yPos, char value)
{
	this->m_tiles[xPos][yPos] = value;
}

size_t Grid::getWidth()
{
	return this->m_width;
}

size_t Grid::getHeight()
{
	return this->m_height;
}

bool Grid::tileIsBlocked(size_t xPos, size_t yPos) 
{
	//TODO!

	return this->m_tiles[xPos][yPos] != '.';
}

std::vector<std::pair<size_t, size_t>> Grid::getAccessibleAdjacentTiles(std::pair<size_t, size_t> pos) {
	std::vector<std::pair<size_t, size_t>> retVec;

	if (pos.first > 0						&& !this->tileIsBlocked(pos.first - 1, pos.second)) retVec.emplace_back(pos.first - 1, pos.second);
	if (pos.second > 0						&& !this->tileIsBlocked(pos.first, pos.second - 1)) retVec.emplace_back(pos.first, pos.second - 1);
	if (pos.first + 1 < this->getWidth()	&& !this->tileIsBlocked(pos.first + 1, pos.second)) retVec.emplace_back(pos.first + 1, pos.second);
	if (pos.second + 1 < this->getHeight()	&& !this->tileIsBlocked(pos.first, pos.second + 1)) retVec.emplace_back(pos.first, pos.second + 1);

	return retVec;
}

void Grid::Update()
{

}
