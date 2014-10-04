#include "Minion.h"

void Minion::doNextMove() {
	if (this->isAlive())
	{
		this->setPosition(this->pathAlgorithm->getNextMove(this->getPosition));
	}
}