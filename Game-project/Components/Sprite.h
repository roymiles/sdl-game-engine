#pragma once

#include <string>

#include "../Component.h"
#include "../Utility/FileHelpers.h" // Access to image file paths
#include "SDL.h"

namespace game { namespace components {

class Sprite : public Component
{
public:
	// Should include all data required for entity to be drawn

	// The image we will load and show on the screen
	SDL_Surface* image = NULL;

	Sprite();
	~Sprite();

	const std::string getName() const override;

	void setup();

	void setImagePath(std::string _imagePath);

private:
	// The path to the image
	std::string imagePath;

	// The unique name of the component
	static const std::string name;
};

} }

