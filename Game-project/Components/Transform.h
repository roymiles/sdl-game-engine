#pragma once

#include "../Component.h"
#include "SDL.h"
#include "../Maths/Vec2.h"

namespace game { namespace components {

using namespace maths;

// static   = stays on screen with relative x, y coordinates
// absolute = position is relative to level
// for example, gui elements will be static as they will stay relative to the screen
enum display { _ABSOLUTE, _STATIC };

/*
 * Most entities will have this component. It defines the entities
 * current position in the world and orientation.
 */
class Transform : public Component
{
public:
	Transform();
	~Transform();

	const std::string getName() const override;

	void setPosition(double _x, double _y);
	void setPosition(Vec2d _position);
	Vec2d getPosition();

	void setDimensions(double _x, double _y, int _height, int _width);

	int getHeight() const;
	int getWidth() const;
	void setHeight(int _height);
	void setWidth(int _width);

	int getX() const;
	int getY() const;

	SDL_Rect getRect();

	// The unique name of the component
	static const std::string name;

	display getDisplayType() const;
	void setDisplayType(const display _displayType);

private:

	Vec2d position;
	Vec2d orientation;

	int height;
	int width;

	display displayType = _ABSOLUTE;
};

} }
