#include "World.h"

namespace game {

World::World()
{
}


World::~World()
{
}

Entity World::createEntity()
{
	// Add to container and then return entity
	return NULL;
}

void World::removeEntity(int id)
{

}

void World::setup()
{
	// Loop through all entities and call setup
	for (auto &entity : entityContainer)
	{
		entity.setup();
	}
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity.setup();
	}
}

}

