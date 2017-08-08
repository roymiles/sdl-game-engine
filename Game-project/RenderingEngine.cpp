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
		std::shared_ptr<Transform> transform = entity.second->getComponent<Transform>();
		SDL_Rect box = transform->getRect();

		std::shared_ptr<Sprite> sprite = entity.second->getComponent<Sprite>();

		// copy the texture to the rendering context
		SDL_RenderCopy(Window::renderer, sprite->getTexture(entity.second->getCurrentState()), NULL, &box); // The current texture depends on the entities state
	}

	// Flip the backbuffer
	// This means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(Window::renderer);
}

}
