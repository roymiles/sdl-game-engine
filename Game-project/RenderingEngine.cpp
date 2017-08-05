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
		// Every entity is drawn inside a box (rectangle)
		SDL_Rect box;

		std::shared_ptr<Transform> transform = entity->getComponent<Transform>();

		Vec2d position = transform->getPosition();
		box.x = position.x;
		box.y = position.y;
		box.w = transform->getWidth();
		box.h = transform->getHeight();

		std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

		// Apply the image
		SDL_BlitSurface(sprite->image, NULL, screenSurface, &box);
	}

	// Update the surface
	// This is only done after all the images are blitsed
	SDL_UpdateWindowSurface(window);
}

}
