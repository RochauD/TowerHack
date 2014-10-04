#include "Minion.h"

Dijkstra* Minion::pathAlgorithm;

void Minion::setPathAlgorithm(Dijkstra& pathAlgorithm) {
	Minion::pathAlgorithm = &pathAlgorithm;
}

void Minion::doNextMove() {
	if (this->isAlive())
	{
		if (Minion::pathAlgorithm != nullptr)
		{
			this->setPosition(Minion::pathAlgorithm->getNextMove(this->getPosition()));
		}
	}
}