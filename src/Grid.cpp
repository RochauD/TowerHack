#include "Grid.h"
#include <fstream>
#include "Minion.h"
#include "Entity.h"
#include "Dijkstra.h"

#include "Renderable.h"

Grid::Grid(std::string& filename, size_t offsetX, size_t offsetY)
{
	this->m_lastUpdateTimePoint = std::chrono::system_clock::now();
	this->m_lastSpawnTimePoint = std::chrono::system_clock::now();
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
				this->m_tileSprites[i][j]->setPosition(static_cast<float>(this->m_offsetX + 20 * j), static_cast<float>(this->m_offsetY + 20 * i));
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
				this->m_tileSprites[i][j]->setPosition(static_cast<float>(this->m_offsetX + 20 * j), static_cast<float>(this->m_offsetY + 20 * i));
			}
		}
	}

	

	this->m_dijkstraAlgorithm = new Dijkstra(this);
	Minion::setPathAlgorithm(this->m_dijkstraAlgorithm);
	this->m_dijkstraAlgorithm->calculateInitialPaths(Position(this->m_height - 1, this->m_width - 1));
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

	return this->m_tiles[xPos][yPos] != '_';
}

std::vector<std::pair<size_t, size_t>> Grid::getAccessibleAdjacentTiles(std::pair<size_t, size_t> pos) {
	std::vector<std::pair<size_t, size_t>> retVec;

	if (pos.first > 0 && !this->tileIsBlocked(pos.first - 1, pos.second)) retVec.emplace_back(pos.first - 1, pos.second);
	if (pos.second > 0 && !this->tileIsBlocked(pos.first, pos.second - 1)) retVec.emplace_back(pos.first, pos.second - 1);
	if (pos.first + 1 < this->getHeight() && !this->tileIsBlocked(pos.first + 1, pos.second)) retVec.emplace_back(pos.first + 1, pos.second);
	if (pos.second + 1 < this->getWidth() && !this->tileIsBlocked(pos.first, pos.second + 1)) retVec.emplace_back(pos.first, pos.second + 1);

	return retVec;
}

std::vector<std::shared_ptr<Entity>> Grid::getEntitiesInRange(std::shared_ptr<Entity> entity) {
	return std::vector<std::shared_ptr<Entity>>();
}

void Grid::Update()
{
	std::vector<std::vector<std::shared_ptr<Entity>>::iterator> toRemove;
	auto elapsed = std::chrono::system_clock::now() - this->m_lastUpdateTimePoint;

	
		this->m_lastSpawnTimePoint = std::chrono::system_clock::now();

		if (/*std::chrono::system_clock::now() - this->m_lastSpawnTimePoint > std::chrono::seconds(2) &&*/ this->m_entities.size() < 100)
		{
			this->m_lastSpawnTimePoint = std::chrono::system_clock::now();
			std::shared_ptr<Entity> temp = std::shared_ptr<Minion>(new Minion(std::string("Entity1.png"), 100, 10, 2, std::chrono::seconds(2), Position(9, 0), Position(this->m_offsetX, this->m_offsetY), true, 1));
				
			this->m_entities.push_back(temp);
		}

		for (auto iter = this->m_entities.begin(); iter != this->m_entities.end(); ++iter)
		{
			if ((*iter)->isAlive()) {
				(*iter)->update(elapsed, this->getEntitiesInRange(*iter));
			}
			else {
				toRemove.push_back(iter);
			}
		}

		for (auto iter = toRemove.begin(); iter != toRemove.end(); ++iter)
		{
			this->m_entities.erase(*iter);
		}

		toRemove.clear();
}
