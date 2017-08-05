#include "KeyDown.h"

namespace game { namespace events {

const std::string KeyDown::name = "KeyDown";

KeyDown::KeyDown()
{
}

KeyDown::~KeyDown()
{
}

const std::string KeyDown::getName() const
{
	return name;
}

} }
