#ifndef ENTITY_H
#define ENTITY_H
#include <chrono>
#include "EntityManager.h"
#include "SFML\System.hpp"

class Entity {
	using Position = std::pair<size_t, size_t>;
	friend class EntityManager;

private:
	int maxHp;
	int hp;
	int damage;
	int attackRange;
	int level;		// other values scale with the level of the entity
	sf::Time attackSpeed;
	std::chrono::time_point<std::chrono::system_clock> lastAttack;
	Position position;
	bool isAlive;

	static sf::Clock clock;

	Entity(int maxHp, int damage, int range, sf::Time atkSpeed, Position position, bool alive, int level);
	
public:	
	bool isAlive();
	void attack(Entity target);
	void takeDamage(int damage);
	void setPosition(Position pos);

	int getDamage();
	int getHp();
	Position getPosition();
};

#endif