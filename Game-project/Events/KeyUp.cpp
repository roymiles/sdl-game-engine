#include "KeyUp.h"

namespace game { namespace events {

const std::string KeyUp::name = "KeyUp";

KeyUp::KeyUp()
{
}

KeyUp::~KeyUp()
{
}

const std::string KeyUp::getName() const
{
	return name;
}

} }
