#include "Transform.h"

#include <string>

namespace game { namespace components {

const std::string name = "Transform";
const unsigned int ID = utilities::hashCode(name.c_str());

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
