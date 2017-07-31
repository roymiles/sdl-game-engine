#pragma once

#include <string>

#include "../Component.h"
#include "SDL.h"

namespace game { namespace components {

class Sprite : public Component
{
public:
	// Should include all data required for entity to be drawn

	// The image we will load and show on the screen
	SDL_Surface* image = NULL;

	// The path to the image
	std::string imagePath;

	Sprite();
	~Sprite();

	void setup();
};

} }

