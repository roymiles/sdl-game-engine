#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "SDL.h"
#include "World.h"
#include "Event.h"

namespace game {

/*
 * This class is used to register and fire events using a container
 * with appropriate callbacks binded to specific inputs
 */
class EventManager
{
public:
	EventManager(std::shared_ptr<World> _world);
	~EventManager();

	/*
	 * Poll SDL_Event to see if any inputs have been pressed
	 * and make the appropriate callback
	 */
	void update(SDL_Event* window_event);

private:
	std::shared_ptr<World> world;

	void triggerEvent(eventPointer e); // Trigger an event
};

}