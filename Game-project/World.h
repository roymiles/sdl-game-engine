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
#include "Entities/UI/Button.h"
#include "Entities/UI/Block.h"

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
	static std::map<std::string, entityPointer> entityContainer;

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

	// Get a list of all the entities that are within a given point x, y
	// @param point - an SDL struct that simply contains the x, y data
	static std::vector<std::shared_ptr<Entity>> getEntitiesAtPoint(SDL_Point &point);

	// Get the entity with the highest layer from a list of entities
	// @param maxLayer - Cap the search to find only entities below a given layer
	//					 For example, you may not care about anything higher than the FOREGROUND
	static std::shared_ptr<Entity> getHighestLayerEntity(std::vector<std::shared_ptr<Entity>> entities, layers maxLayer);

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

