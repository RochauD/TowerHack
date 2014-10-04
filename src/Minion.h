#include "Entity.h"
#include "Dijkstra.h"


class Minion : public Entity {
private:
	static Dijkstra* pathAlgorithm;
	sf::Time movementSpeed;

public:
	static void setPathAlgorithm(Dijkstra& pathAlgorithm);
	void doNextMove();
};