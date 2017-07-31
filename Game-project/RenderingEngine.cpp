#include "RenderingEngine.h"

namespace game {

RenderingEngine::RenderingEngine(std::shared_ptr<World> _world, SDL_Window  *_window, SDL_Surface *_screenSurface)
{
	world		  = _world;
	window		  = _window;
	screenSurface = _screenSurface;
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::update()
{
	std::list<entityPointer> drawableEntities;
	drawableEntities = world->getEntitiesWithComponent<Sprite>();

	// Draw all the sprites to the screen
	for (auto &entity : drawableEntities)
	{
		std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

		//entity.getComponent<Transform>()->position;

		// Apply the image
		SDL_BlitSurface(sprite->image, NULL, screenSurface, NULL);
		// Update the surface
		SDL_UpdateWindowSurface(window);
	}
}

}
