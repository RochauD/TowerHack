#ifndef ENTITY_H
#define ENTITY_H
#include <chrono>

class Entity {
	using Position = std::pair<size_t, size_t>;

private:
	int maxHp;
	int hp;
	int damage;
	int attackRange;
	float attackSpeed;
	std::chrono::time_point<std::chrono::system_clock> lastAttack;
	Position position;
	
public:
	void attack(Entity target);
	void takeDamage(int damage);

	int getDamage();
	Position getPosition();
};

#endif