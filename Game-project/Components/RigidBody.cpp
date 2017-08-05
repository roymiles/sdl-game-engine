#include <string>

#include "RigidBody.h"

namespace game { namespace components {

const std::string RigidBody::name = "RigidBody";
const unsigned int RigidBody::ID  = utilities::hashCode(name);


RigidBody::RigidBody(SDL_Rect _collisionMesh)
{
	collisionMesh = _collisionMesh;
}


RigidBody::~RigidBody()
{
}

std::string RigidBody::getName() const
{
	return name;
}

unsigned int RigidBody::getID() const
{
	return ID;
}

} }
