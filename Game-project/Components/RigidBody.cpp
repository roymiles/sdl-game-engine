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

const std::string RigidBody::getName() const
{
	return name;
}

} }
