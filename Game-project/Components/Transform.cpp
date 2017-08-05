#include "Transform.h"

#include <string>

namespace game { namespace components {

const std::string Transform::name = "Transform";

Transform::Transform()
{
}


Transform::~Transform()
{
}

const std::string Transform::getName() const
{
	return name;
}

void Transform::setPosition(double _x, double _y)
{
	position = Vec2d(_x, _y);
}

Vec2d Transform::getPosition()
{
	return position;
}

void Transform::setDimensions(double _x, double _y, int _height, int _width)
{
	position = Vec2d(_x, _y);
	height = _height;
	width = _width;
}

int Transform::getHeight() const
{
	return height;
}

int Transform::getWidth() const
{
	return width;
}

void Transform::setHeight(int _height)
{
	height = _height;
}

void Transform::setWidth(int _width)
{
	width = _width;
}

} }
