#include "World.h"

// To generate the unique entity keys
#include "Utility/Random.h"

#include <sstream>

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
	std::string randomKey = randomString(7);

	entityContainer[entity->getName() + "_" + randomKey] = entity;

	return randomKey;
}

void World::createEntity(entityPointer entity, std::string key)
{
	// Add to container and then return entity
	entityContainer[entity->getName() + "_" + key] = entity;
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
        
	for (int x = 0; x < Window::WIDTH; x += 100)
	{
		for (int y = 0; y < Window::HEIGHT; y += 100)
		{
			std::shared_ptr<Floor> floor(new Floor(x, y));
			//floor = std::make_shared<Floor>(new Floor(x, y));
			std::stringstream ss;

			ss << x << "_" << y;
			createEntity(floor, ss.str());
		}
	}
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
			entitiesWithComponent[entity.second->getName() + "_" + randomString(7)] = entity.second;
		}
	}

	return entitiesWithComponent;
}

}

