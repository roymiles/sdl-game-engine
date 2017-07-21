#include "PhysicsEngine.h"

namespace game {

PhysicsEngine::PhysicsEngine(std::shared_ptr<World> _world)
{
	world = _world;
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::update()
{
	// Loop through all the entities with a RigidBody component
	for (auto &entity : world->entityContainer)
	{
		// Check if this entity has registered for this event
		if (entity.second.hasComponent<RigidBody>())
		{
			// do stuff
		}
	}
}


}
