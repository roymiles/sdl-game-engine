#include "MouseButtonUp.h"

namespace game { namespace events {

const std::string MouseButtonUp::name = "MouseButtonUp";

MouseButtonUp::MouseButtonUp()
{

}

MouseButtonUp::MouseButtonUp(int _x, int _y)
{
	x = _x;
	y = _y;
}

MouseButtonUp::~MouseButtonUp()
{
}

int MouseButtonUp::getX()
{
	return x;
}

int MouseButtonUp::getY()
{
	return y;
}

const std::string MouseButtonUp::getName() const
{
	return name;
}

} }

