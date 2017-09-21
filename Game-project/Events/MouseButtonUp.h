#pragma once

#include "../Event.h"

namespace game { namespace events {

class MouseButtonUp : public Event
{
public:
	MouseButtonUp();
	MouseButtonUp(int _x, int _y);
	~MouseButtonUp();

	const std::string getName() const override;
	// This needs to be public so that it can easily be read without
	// creating unnecessary event instances
	static const std::string name;

	int MouseButtonUp::getX();
	int MouseButtonUp::getY();

private:
	int x, y; // coordinates of where the mouse button is released
};

} }

