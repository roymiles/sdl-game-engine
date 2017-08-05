#include "EventManager.h"

namespace game {

EventManager::EventManager(std::shared_ptr<World> _world)
{
	world = _world;
}


EventManager::~EventManager()
{
}

void EventManager::update(SDL_Event* window_event)
{
	if (SDL_PollEvent(window_event)) {
		switch (window_event->type) {
			/* Keyboard event */
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				triggerEvent<KeyUp>();
				break;

				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				//triggerEvent(KEY_DOWN);
				break;

			default:
				break;
		}
	}
}

}
