#pragma once

#include "World.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"

namespace game {

using namespace components;

/*
 * This class is responsible for drawing all the entities on screen and in
 * the right order. 
 * 1. Do transparent images appear transparent through SDL?
 * 2. Only draw entities that are within the window
 */
class RenderingEngine
{
public:
	RenderingEngine(std::shared_ptr<World> _world, SDL_Window  *_window, SDL_Surface *_screenSurface);
	~RenderingEngine();

	void update();

private:
	std::shared_ptr<World> world;
	// The following pointers cant be unique_ptr or shared_ptr because they are passed
	// into SDL_ functions which only accept raw pointers.
	SDL_Window	*window;
	SDL_Surface *screenSurface;
};

}

