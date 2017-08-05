#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Entity.h"
#pragma message("Maybe the map creation could be exported into another class?")
#include "Entities/Character.h" 

namespace game {

using namespace entities;

class World
{
public:
	World();
	~World();

	// Each entity is  identified by a unique string
	std::map<std::string, entityPointer> entityContainer;
	
	// For a given identifier, return the entity within the container
	entityPointer World::getEntity(std::string id);

	// Add an entity to the container and return the identifier
	std::string createEntity(entityPointer entity);
	void removeEntity(int id);

	void setup();
	void update();

	// Return a list of all entities with a given component T
	template<typename T>
	std::list<entityPointer> getEntitiesWithComponent()
	{
		std::list<entityPointer> entitiesWithComponent;
		for (auto &entity : entityContainer)
		{
			if (entity.second->hasComponent<T>())
			{
				entitiesWithComponent.push_back(entity.second);
			}
		}

		return entitiesWithComponent;
	}
};

}

