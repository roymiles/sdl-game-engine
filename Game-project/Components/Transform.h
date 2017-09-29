#pragma once

#include "../Component.h"
#include "SDL.h"
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

	const std::string getName() const override;

	void setPosition(int _x, int _y);
	void setPosition(Vec2i _position);
	Vec2i getPosition();

	void setDimensions(int _x, int _y, int _height, int _width);

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

	Vec2i position;
	//Vec2d orientation; // not currently used

	int height;
	int width;

	display displayType = _ABSOLUTE;
};

} }
