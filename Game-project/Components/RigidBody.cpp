#include <string>

#include "RigidBody.h"

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

void RigidBody::setCollisionMesh(SDL_Rect _collisionMesh)
{
	collisionMesh = _collisionMesh;
}

const std::string RigidBody::getName() const
{
	return name;
}

} }
