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
	std::map<std::string, Entity> entityContainer;
	
	// For a given identifier, return the entity within the container
	Entity World::getEntity(std::string id);

	// Add an entity to the container and return the identifier
	std::string createEntity(std::shared_ptr<Entity> entity);
	void removeEntity(int id);

	void setup();
	void update();
};

}

