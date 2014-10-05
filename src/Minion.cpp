#include "Minion.h"

Dijkstra* Minion::pathAlgorithm;

Minion::Minion()
{

}

Minion::Minion(std::string filename, int maxHp, int damage, int range, std::chrono::milliseconds atkSpeed, Position position, Position offset, bool alive, int level, std::chrono::milliseconds movementSpeed) : Entity(filename, maxHp, damage, range, atkSpeed, position, offset, alive, level) {
	this->setAlive(alive);
	this->movementSpeed = movementSpeed;
}

void Minion::setPathAlgorithm(Dijkstra* pathAlgorithm) {
	Minion::pathAlgorithm = pathAlgorithm;
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

void Minion::setAlive(bool alive) {
	Entity::setAlive(alive);

	if (this->isAlive() != alive && alive)
	{
		this->m_lastMoveTimePoint = std::chrono::steady_clock::now();
	}
}

void Minion::update(SysClock elapsed, std::vector<std::shared_ptr<Entity>>& entitiesInRange) {
	if (this->isAlive())
	{
		Entity::update(elapsed, entitiesInRange);

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->m_lastMoveTimePoint) > this->movementSpeed)
		{
			this->doNextMove();
			this->m_lastMoveTimePoint = std::chrono::time_point_cast<SysClock>(std::chrono::steady_clock::now() + this->movementSpeed);
		}
	}
}