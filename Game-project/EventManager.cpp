#include "EventManager.h"
#include <iostream>

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
	// Note: the scope within the case statements is because there are variable intialisations
	// this also ensures the variables are destroyed upon going out of the case statement (scope)
	if (SDL_PollEvent(window_event)) {
        switch (window_event->type) {
			/* Keyboard event */
            case SDL_KEYDOWN:
                triggerEvent(KeyDown::name);

				/* Check the SDLKey values to see what key is pressed */
				switch (window_event->key.keysym.sym) {
					case SDLK_LEFT:
						triggerEvent(LeftKey::name);
						break;
					case SDLK_RIGHT:
						triggerEvent(RightKey::name);
						break;
					case SDLK_UP:
						triggerEvent(UpKey::name);
						break;
					case SDLK_DOWN:
						triggerEvent(DownKey::name);
						break;
					default:
						break;
				}
                break;
			case SDL_KEYUP:
				triggerEvent(KeyUp::name);
				break;

			default:
				break;
		}
	}
    
    
}

// Trigger an event
void EventManager::triggerEvent(std::string name)
{
	for (auto &entity : world->entityContainer)
	{
		// Check if this entity has registered for this event
		if (entity.second->hasRegisteredEvent(name)) {
			entity.second->onEvent(name);
		}
	}
}
    
}
