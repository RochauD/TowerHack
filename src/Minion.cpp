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

void Minion::update() {
	if (this->isAlive())
	{
		Entity::update();

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->m_lastMoveTimePoint) > this->movementSpeed)
		{
			this->doNextMove();
			this->m_lastMoveTimePoint = std::chrono::time_point_cast<std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>>(std::chrono::steady_clock::now() + this->movementSpeed);
		}
	}
}