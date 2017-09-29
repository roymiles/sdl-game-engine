#pragma once

#include "Dependancies/SDL/Windows/include/SDL.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	// The maximum height and widths of the current level
	static const SDL_Rect DIMENSIONS;
};

