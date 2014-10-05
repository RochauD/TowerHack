#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(std::string filename, int maxHp, int damage, int range, std::chrono::milliseconds atkSpeed, Position position, Position offset, bool alive, int level) {
	this->maxHp = maxHp;
	this->hp = maxHp;
	this->damage = damage;
	this->attackRange = range;
	this->attackSpeed = atkSpeed;
	this->position = position;
	this->alive = alive;
	this->level = level;
	this->m_offset = offset;

	this->m_sprite = std::shared_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
	StandardTexture* temp = this->m_sprite->GetTexture();
	temp->LoadTexture("Entity1.png");
	this->m_sprite->SetZIndex(10001);
	this->m_sprite->SetVisibilityFlag(false);
	this->m_sprite->Show(true);
	this->m_sprite->UpdatePositions();
	this->m_sprite->UpdateTexCoords();
	this->m_sprite->setPosition(static_cast<float>(this->getPosition().second * this->m_sprite->GetTexture()->GetTextureRect().width + this->m_offset.first), static_cast<float>(this->getPosition().first * this->m_sprite->GetTexture()->GetTextureRect().height + this->m_offset.second));

	
}

void Entity::setAlive(bool alive) {
	if (this->alive != alive && alive)
	{
		this->m_timeSinceLastAttack = std::chrono::system_clock::now();
	}

	this->alive = alive;
}

bool Entity::isAlive() {
	return this->alive;
}

void Entity::attack(Entity target) {
	if (this->isAlive())
	{
		target.takeDamage(this->getDamage());
	}
}

void Entity::takeDamage(int damage) {
	if (this->isAlive() && this->getHp() < damage)
	{
		this->hp = 0;
		this->alive = false;
	}
}

void Entity::update(SysClock elapsed, std::vector<std::shared_ptr<Entity>>& entitiesInRange) {
	// TODO!
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
	this->m_sprite->setPosition(static_cast<float>(this->getPosition().second * this->m_sprite->GetTexture()->GetTextureRect().width + this->m_offset.first), static_cast<float>(this->getPosition().first * this->m_sprite->GetTexture()->GetTextureRect().height + this->m_offset.second));
}