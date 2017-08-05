#include "RenderingEngine.h"
#include "Window.h"

namespace game {

RenderingEngine::RenderingEngine(std::shared_ptr<World> _world)
{
	world = _world;
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::update()
{
	std::map<std::string, entityPointer> drawableEntities;
	Sprite sprite;
	drawableEntities = world->getEntitiesWithComponent(sprite.getName());

	// Clear the screen
	SDL_RenderClear(Window::renderer);

	// Draw all the sprites to the screen
	for (auto &entity : drawableEntities)
	{
		// Every entity is drawn inside a box (rectangle)
		SDL_Rect box;

		std::shared_ptr<Transform> transform = entity.second->getComponent<Transform>();

		Vec2d position = transform->getPosition();
		box.x = position.x;
		box.y = position.y;
		box.w = transform->getWidth();
		box.h = transform->getHeight();

		std::shared_ptr<Sprite> sprite = entity.second->getComponent<Sprite>();

		// copy the texture to the rendering context
		SDL_RenderCopy(Window::renderer, sprite->imageTexture, NULL, &box);
	}

	// Flip the backbuffer
	// This means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(Window::renderer);
}

}
