#include "Entity.h"

Entity::Entity(int maxHp, int damage, int range, sf::Time atkSpeed, Position position, bool alive, int level) {
	this->maxHp = maxHp;
	this->hp = maxHp;
	this->damage = damage;
	this->attackRange = range;
	this->attackSpeed = atkSpeed;
	this->position = position;
	this->isAlive = alive;
	this->level = level;
}

bool Entity::isAlive() {
	return this->isAlive;
}

void Entity::attack(Entity target) {
	if (this->isAlive)
	{
		target.takeDamage(this->getDamage());
	}
}

void Entity::takeDamage(int damage) {
	if (this->isAlive && this->getHp() < damage)
	{
		this->hp = 0;
		this->isAlive = false;
	}
}

int Entity::getHp() {
	return this->hp * this->level;
}

int Entity::getDamage() {
	return this->damage * this->level;
}

Entity::Position Entity::getPosition() {
	return this->position;
}

void Entity::setPosition(Position pos) {
	this->position = pos;
}