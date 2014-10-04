#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <set>
#include "Entity.h"
#include <string>

class EntityManager {
private:
	std::set<Entity> allEntities;
	Entity CreateEntity(std::string identifier);

};

#endif