#include "RigidBody.h"

namespace game { namespace components {

RigidBody::RigidBody(SDL_Rect _collisionMesh)
{
	collisionMesh = _collisionMesh;
}


RigidBody::~RigidBody()
{
}

} }
