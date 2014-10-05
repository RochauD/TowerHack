#ifndef ENTITY_H
#define ENTITY_H
#include "Grid.h"
#include <chrono>
#include "Renderable.h"
#include <memory>

using SysClock = std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>;

class Entity {

protected:
	using Position = std::pair<size_t, size_t>;
	Entity(std::string filename, int maxHp, int damage, int range, std::chrono::milliseconds atkSpeed, Position position, Position offset, bool alive, int level);
	Entity();
private:
	std::shared_ptr<StaticSprite<StandardTexture>> m_sprite;
	int maxHp;
	int hp;
	int damage;
	int attackRange;
	int level;		// other values scale with the level of the entity
	std::chrono::milliseconds attackSpeed;
	std::chrono::system_clock::time_point m_timeSinceLastAttack;
	Position position;
	Position m_offset;
	bool alive;

	static sf::Clock clock;


	
public:	
	bool isAlive();
	void setAlive(bool alive);
	void attack(Entity target);
	void takeDamage(int damage);
	void setPosition(Position pos);
	virtual void update(SysClock elapsed, std::vector<std::shared_ptr<Entity>>& entitiesInRange);

	int getDamage();
	int getHp();
	Position getPosition();
};

#endif