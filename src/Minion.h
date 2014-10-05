#ifndef MINION_H
#define MINION_H

#include "Entity.h"
#include "Dijkstra.h"



class Minion : public Entity {
private:
	static Dijkstra* pathAlgorithm;
	std::chrono::milliseconds movementSpeed;
	std::chrono::system_clock::time_point m_lastMoveTimePoint;
	void doNextMove();

public:
	Minion();
	Minion(std::string filename, int maxHp, int damage, int range, std::chrono::milliseconds atkSpeed, Position position, Position offset, bool alive, int level);

	static void setPathAlgorithm(Dijkstra* pathAlgorithm);
	void update(SysClock elapsed, std::vector<std::shared_ptr<Entity>>& entitiesInRange);
	void setAlive(bool alive);
};

#endif

