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
			case SDL_KEYDOWN :
			{
				std::shared_ptr<KeyDown> keyDown(new KeyDown());
				triggerEvent(keyDown);

				/* Check the SDLKey values to see what key is pressed */
				switch (window_event->key.keysym.sym) {
					case SDLK_LEFT:
					{
						std::shared_ptr<LeftKey> leftKey(new LeftKey());
						triggerEvent(leftKey);
						break;
					}
					case SDLK_RIGHT:
					{
						std::shared_ptr<RightKey> rightKey(new RightKey());
						triggerEvent(rightKey);
						break;
					}
					case SDLK_UP:
					{
						std::shared_ptr<UpKey> upKey(new UpKey());
						triggerEvent(upKey);
						break;
					}
					case SDLK_DOWN:
					{
						std::shared_ptr<DownKey> downKey(new DownKey());
						triggerEvent(downKey);
						break;
					}
					default:
						break;
				}
				break;
			}
			case SDL_KEYUP:
			{
				std::shared_ptr<KeyUp> keyUp(new KeyUp());
				triggerEvent(keyUp);
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				//Get mouse position
				std::cout << "mouse up" << std::endl;
				int x, y;
				SDL_GetMouseState(&x, &y);
				std::shared_ptr<MouseButtonUp> mouseButtonUp(new MouseButtonUp(x, y));
				triggerEvent(mouseButtonUp);
				break;
			}
			default:
				break;
		}
	}
    
    
}

// Trigger an event
// Loops through all the entities and checks if the entity has registered
// for the event, if so it will call onEvent for the entity to handle accordingly
//void EventManager::triggerEvent(std::string eventName)
void EventManager::triggerEvent(std::shared_ptr<Event> event_ptr)
{
	for (auto &entity : world->entityContainer)
	{
		// Check if this entity has registered for this event
		if (entity.second->hasRegisteredEvent(event_ptr->getName())) {
			entity.second->onEvent(event_ptr);
		}
	}
}
    
}
