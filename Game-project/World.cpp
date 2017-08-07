#include "World.h"

// To generate the unique entity keys
#include "Utility/Random.h"

namespace game {

using namespace utilities;

World::World()
{
}


World::~World()
{
}

entityPointer World::getEntity(std::string key)
{
	return entityContainer[key];
}

std::string World::createEntity(entityPointer entity)
{
	// Add to container and then return entity
	
	// Create a random key, this will be the unique key for this entitity
	// May need to check this key does not already exist first!
	std::string randomKey = randomString(5);

	entityContainer[entity->getName() + "_" + randomKey] = entity;

	return randomKey;
}

void World::removeEntity(std::string key)
{
	entityContainer.erase(key);
}

void World::setup()
{
	// -------------- Temporary ---------------
	// TODO: This needs to be ported over to a LevelManager class
	// Create entities for level
	std::shared_ptr<Character> character(new Character());
	createEntity(character);

	std::shared_ptr<Box> box(new Box());
	createEntity(box);
	// ----------------------------------------

	// Loop through all the created entities and call setup
	for (auto &entity : entityContainer)
	{
		// Calling setup on each entity will also internally call
		// setup on each of their components
		entity.second->setup();
	}
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity.second->update();
	}
}

std::map<std::string, entityPointer> World::getEntitiesWithComponent(std::string key)
{
	std::map<std::string, entityPointer> entitiesWithComponent;
	for (auto &entity : entityContainer)
	{
		if (entity.second->hasComponent(key))
		{
			entitiesWithComponent[entity.second->getName()] = entity.second;
		}
	}

	return entitiesWithComponent;
}

}

