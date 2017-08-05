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
        std::cout << window_event->type << std::endl;
        switch (window_event->type) {
			/* Keyboard event */
            case SDL_KEYDOWN: {
                KeyDown k;
                triggerEvent(k.getName());
                break;
            }
			case SDL_KEYUP: {
				KeyUp k;
				triggerEvent(k.getName());
				break;
			}
				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				//triggerEvent(KEY_DOWN);
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
