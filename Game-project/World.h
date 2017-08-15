#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <list>

#include "Entity.h"
#include "Entities/Camera.h"
#include "Entities/Character.h" 
#include "Entities/Box.h"
#include "Entities/Floor.h"

namespace game {

using namespace entities;

enum gameState : int{
	Menu	= 0,
	Level1	= 1
};

class World
{
public:
	World();
	~World();

	// Each entity is  identified by a unique string
	std::map<std::string, entityPointer> entityContainer;

	// Current game state
	gameState currentGameState;
	
	// For a given identifier, return the entity within the container
	entityPointer getEntity(std::string id);

	// Return the first occurance of an entity type
	template<typename T>
	std::shared_ptr<T> getEntity()
	{
		for (auto const &entity : entityContainer)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(entity.second))
			{
				return ptr;
			}
		}

		return nullptr;
	}

	// Add an entity to the container and return the identifier
	std::string createEntity(entityPointer entity);
	void createEntity(entityPointer entity, std::string key);

	void removeEntity(std::string key);

	void setup();
	void update();

	// Return a list of all entities with a given component
	std::map<std::string, entityPointer> getEntitiesWithComponent(std::string key);
};

}

