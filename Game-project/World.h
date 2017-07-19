#pragma once

#include <vector>
#include <string>

#include "Entity.h"

namespace game {

class World
{
public:
	World();
	~World();

	std::vector<Entity> entityContainer;
	
	Entity createEntity();
	void removeEntity(int id);

	void setup();
	void update();
};

}

