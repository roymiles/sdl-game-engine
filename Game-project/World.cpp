#include "World.h"

namespace game {

World::World()
{
}


World::~World()
{
}

Entity World::getEntity(std::string id)
{
	return entityContainer[id];
}

std::string World::createEntity(std::shared_ptr<Entity> entity)
{
	// Add to container and then return entity
	return "1";
}

void World::removeEntity(int id)
{

}

void World::setup()
{
	// Create all the objects in the world and add them to the container
#pragma message("Maybe the map creation could be exported into another class?")
	// These should be shared pointers because they are passed into functions
	std::shared_ptr<Entity> character(new Character());
	std::string characterId = createEntity(character);

	// Loop through all the created entities and call setup
	for (auto &entity : entityContainer)
	{
		entity.second.setup();
	}
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity.second.setup();
	}
}

}

