#include "Dijkstra.h"

Dijkstra::Dijkstra(Grid &grid) {
	this->grid = &grid;

	this->gridNodes = std::set<Position>();

	for (size_t i = 0; i < grid.getWidth(); i++)
	{
		std::vector<size_t> tempSizeVec;
		std::vector<Position> tempPosVec;
		std::vector<bool> tempBoolVec;

		for (size_t j = 0; j < grid.getHeight(); j++)
		{
			if (!this->grid->tileIsBlocked(i, j))
			{
				this->gridNodes.insert(Position(i, j));
			}

			tempBoolVec.push_back(false);
			tempSizeVec.push_back(INT_MAX);
			tempPosVec.emplace_back(INT_MAX, INT_MAX);
		}
		this->distance.push_back(tempSizeVec);
		this->parent.push_back(tempPosVec);
		this->scanned.push_back(tempBoolVec);
	}
}

void Dijkstra::removeGridNode(size_t xPos, size_t yPos) {
	this->gridNodes.erase(Position(xPos, yPos));
}

Position Dijkstra::getNextMove(Position currPos) {
	return this->getNextMove(currPos.first, currPos.second);
}

Position Dijkstra::getNextMove(size_t xPos, size_t yPos) {
	return this->parent[xPos][yPos];
}

void Dijkstra::calculateInitialPaths(Position end) {
	this->parent[end.first][end.second] = end;	//by definition: end is the parent of end
	this->distance[end.first][end.second] = 0;


	std::vector<ValPosition> queue;

	queue.push_back(ValPosition(end, 0));

	while (!queue.empty())
	{
		ValPosition node = queue.front();
		queue.erase(queue.begin());

		std::vector<Position> adjTiles = this->grid->getAccessibleAdjacentTiles(node.first);

		for each (Position adjNode in adjTiles)
		{
			if (!this->scanned[node.first.first][node.first.second] && this->getDistance(node) + 1 < this->getDistance(adjNode))
			{
				this->setDistance(adjNode, (this->getDistance(node) + 1));	// set new distance
				this->setParent(adjNode, node);								// set new parent node

				ValPosition adjNodeValPos = ValPosition(adjNode, this->getDistance(adjNode));

				for (auto iter = queue.begin(); iter != queue.end(); iter++)
				{
					if (adjNode.first == iter->first.first && adjNode.second == iter->first.second)
					{
						queue.erase(iter);
					}
				}

				queue.push_back(adjNodeValPos);

				std::sort(queue.begin(), queue.end(), [](ValPosition& a, ValPosition& b){return a.second < b.second; });
			}
		}

		this->scanned[node.first.first][node.first.second] = true;
	}
}

size_t Dijkstra::getDistance(ValPosition vPos) {
	return this->distance[vPos.first.first][vPos.first.second];
}

size_t Dijkstra::getDistance(Position vPos) {
	return this->distance[vPos.first][vPos.second];
}

void Dijkstra::setDistance(ValPosition vPos, size_t dist) {
	this->distance[vPos.first.first][vPos.first.second] = dist;
}

void Dijkstra::setDistance(Position vPos, size_t dist) {
	this->distance[vPos.first][vPos.second] = dist;
}

void Dijkstra::setParent(Position pos, ValPosition vPos) {
	this->parent[pos.first][pos.second] = vPos.first;
}