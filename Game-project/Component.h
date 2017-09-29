#pragma once

#include <memory>
#include <string>

#include "SDL.h"
#include "Utility/Common.h"

namespace game {

// static   = stays on screen with relative x, y coordinates
// absolute = position is relative to level
// for example, gui elements will be static as they will stay relative to the screen
enum display { _ABSOLUTE, _STATIC };

class Component
{
public:
	Component();
	virtual ~Component() = 0;

	virtual const std::string getName() const = 0;

	virtual void setup() {}
	virtual void update() {}

	// Virtual functions overriden by Transform component
	// Having these functions as virtual removes the need to downcast the component
	// inside the rendering engine loop. This drastically improves performance

	// Transform
	virtual SDL_Rect getRect() { return SDL_Rect(); }
	virtual display getDisplayType() const { return _ABSOLUTE; }

	// Sprite
	virtual int getLayer() const { return -1; }

	//bool Component::operator==(const Component &other) const {};
	//bool Component::operator!=(const Component &other) const {};
};

typedef std::unique_ptr<Component> componentPointer;

}