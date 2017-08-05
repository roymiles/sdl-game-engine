#include <string>

#include "RigidBody.h"

namespace game { namespace components {

const std::string RigidBody::name = "RigidBody";

RigidBody::RigidBody(SDL_Rect _collisionMesh)
{
	collisionMesh = _collisionMesh;
}


RigidBody::~RigidBody()
{
}

const std::string RigidBody::getName() const
{
	return name;
}

} }
