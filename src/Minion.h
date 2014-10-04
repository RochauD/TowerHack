#include "Entity.h"
#include "Dijkstra.h"

class Minion : public Entity {
	using Position = std::pair<size_t, size_t>;

private:
	static Dijkstra* pathAlgorithm;
	sf::Time movementSpeed;

public:
	void doNextMove();
};