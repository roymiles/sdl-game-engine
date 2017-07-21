#pragma once

#include "World.h"
#include "Components/RigidBody.h"

namespace game {

using namespace components;

class PhysicsEngine
{
public:
	PhysicsEngine(std::shared_ptr<World> _world);
	~PhysicsEngine();

	void update();

private:
	std::shared_ptr<World> world;
};

}

