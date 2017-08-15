#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "SDL.h"
#include "World.h"
#include "Event.h"

// All the event types
#include "Events/KeyUp.h"
#include "Events/KeyDown.h"
#include "Events/UpKey.h"
#include "Events/RightKey.h"
#include "Events/DownKey.h"
#include "Events/LeftKey.h"

namespace game {

using namespace events;

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

	// Calls onEvent for every entity registering to the triggered event
	void triggerEvent(std::string eventName);
};

}
