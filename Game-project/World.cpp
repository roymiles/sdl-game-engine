#include "World.h"

namespace game {

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
	// - May need to check this key does not already exist first!
	std::string randomKey = randomString(5);

	entityContainer[randomKey] = entity;

	return randomKey;
}

void World::removeEntity(int id)
{

}

void World::setup()
{
	// Create all the objects in the world and add them to the container
#pragma message("Maybe the map creation could be exported into another class?")
	// These should be shared pointers because they are passed into functions
	entityPointer character(new Character());
	std::string characterId = createEntity(character);

	// Loop through all the created entities and call setup
	for (auto &entity : entityContainer)
	{
		entity.second->setup();
	}
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity.second->setup();
	}
}

}

