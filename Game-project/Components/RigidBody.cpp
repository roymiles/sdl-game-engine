#include <string>

#include "RigidBody.h"
#include "../World.h"

namespace game { namespace components {

const std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody()
{
	mass	   = 1;
	elasticity = 1;
}


RigidBody::~RigidBody()
{
}

void RigidBody::setup(int entityId)
{
	// Add this entity to the list entities with rigid body component
	World::rigidBodyEntities.push_back(entityId);
}

const std::string RigidBody::getName() const
{
	return name;
}

} }
