#include "Transform.h"

#include <string>

namespace game { namespace components {

const std::string Transform::name = "Transform";
const unsigned int Transform::ID = utilities::hashCode(name);

Transform::Transform()
{
}


Transform::~Transform()
{
}

std::string Transform::getName() const
{
	return name;
}

unsigned int Transform::getID() const
{
	return ID;
}

} }
