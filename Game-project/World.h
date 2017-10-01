#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <list>

#pragma message("Should be ported over to a time class")
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
//#define DEBUG_TIME 1

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
	static std::vector<entityPointer> entityContainer;

	// All the ids of the drawable entities are stored in a compact form
	// The first index is the layer. This improves performance
	static std::vector<std::vector<int>> renderUpdateEntities; // All entities that need to be drawn on current update
	static std::vector<std::vector<int>> spriteEntities; // All entities with sprite component

	// List of all physics entities that need to be updated
	static std::vector<int> physicsUpdateEntities; // All entities that have had a physics event this frame
	static std::vector<int> rigidBodyEntities; // All entities with rigidBody component

	// Serialise entity container and write to a file
	void serializeEntityContainer(const std::string& fileName);

	// Current game state
	gameState currentGameState;
	
	// For a given identifier, return the entity within the container
	entityPointer getEntity(std::string id);

	// Return the first occurance of an entity type
	template<typename T>
	static std::shared_ptr<T> getEntity()
	{
		for (auto const &entity : entityContainer)
		{
			if (std::shared_ptr<T> ptr = std::static_pointer_cast<T>(entity))
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
	static int createEntity(entityPointer entity);
	static int createEntity(entityPointer entity, std::string key);

	void removeEntity(std::string key);

	void setup();
	void update();

	// Return a list of all entities with a given component
	template<typename T>
	std::vector<entityPointer> getEntitiesWithComponent()
	{
		std::vector<entityPointer> entitiesWithComponent;
		entitiesWithComponent.reserve(entityContainer.size());
		for (auto const &entity : entityContainer)
		{
			if (entity->hasComponent<T>())
			{
				// Add a random key at the end to avoid entities of the same type overwriting
				entitiesWithComponent.push_back(entity);
			}
		}

		return entitiesWithComponent;
	}

	// Convert screen x,y coordinates to world x,y coordinates
	static maths::Vec2i screenToWorldCoordinates(maths::Vec2i screenCoordinates);
};

}

