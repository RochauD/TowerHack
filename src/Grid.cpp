#include "Grid.h"
#include <fstream>
#include <math.h>
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
	std::vector<std::shared_ptr<Entity>> retVec;

	if (this->m_entities.size() > 0)
	{
		for (size_t i = std::max(0, static_cast<int>(entity->getPosition().first) - entity->getRange()); i < std::min(this->getHeight() - 1, entity->getPosition().first + entity->getRange()); i++)
		{
			for (size_t j = std::max(0, static_cast<int>(entity->getPosition().second) - entity->getRange()); j < std::min(this->getWidth() - 1, entity->getPosition().second + entity->getRange()); j++)
			{
				for each (const std::shared_ptr<Entity>& entity2 in this->m_entities)
				{
					if (entity->getPosition() != entity2->getPosition() && entity2->getPosition() == Position(i,j))
					{
						retVec.push_back(entity2);
					}
				}
			}
		}
	}

	return retVec;
}

void Grid::Update()
{
	static bool x = true;
	std::vector<std::vector<std::shared_ptr<Entity>>::iterator> toRemove;
	auto elapsed = std::chrono::steady_clock::now() - this->m_lastUpdateTimePoint;

	auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->m_lastSpawnTimePoint);

	if (elapsed2 > std::chrono::milliseconds(500) && this->m_entities.size() < 5)
	{
		this->m_lastSpawnTimePoint = std::chrono::system_clock::now();

		std::shared_ptr<Entity> temp;

		if (x)
		{
			x = !x;
			temp = std::shared_ptr<Minion>(new Minion(std::string("Entity1.png"), 100, 10, 5, std::chrono::seconds(2), Position(0, 0), Position(this->m_offsetX, this->m_offsetY), true, 1, std::chrono::milliseconds(90)));
		}
		else {
			x = !x;
			temp = std::shared_ptr<Minion>(new Minion(std::string("Entity2.png"), 150, 7, 5, std::chrono::seconds(1), Position(0, 0), Position(this->m_offsetX, this->m_offsetY), true, 1, std::chrono::milliseconds(200)));
		}

		this->m_entities.push_back(temp);
	}

	for (auto iter = this->m_entities.begin(); iter != this->m_entities.end(); ++iter)
	{
		if ((*iter)->isAlive() && (*iter)->getPosition() != Position(this->m_height - 1, this->m_width - 1)) {
			(*iter)->update();
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
