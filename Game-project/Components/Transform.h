#pragma once

#include "../Component.h"

#include "../Maths/Vec2.h"

namespace game { namespace components {

using namespace maths;

/*
 * Most entities will have this component. It defines the entities
 * current position in the world and orientation.
 */
class Transform : public Component
{
public:
	Transform();
	~Transform();

	std::string getName() const override;
	unsigned int getID() const override;

	void setPosition(double _x, double _y);
	Vec2d getPosition();

	void setDimensions(double _x, double _y, int _height, int _width);

	int getHeight() const;
	int getWidth() const;
	void setHeight(int _height);
	void setWidth(int _width);

private:
	// The unique name/ID of the component
	static const std::string name;
	static const unsigned int ID;

	Vec2d position;
	Vec2d orientation;

	int height;
	int width;
};

} }
