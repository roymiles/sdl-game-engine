#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "../World.h"

namespace game { namespace events {

enum eventID {
	KEY_DOWN = 0
	//... add more
};

/*
 * This class is used to register and fire events using a container
 * with appropriate callbacks binded to specific inputs
 */
class EventManager
{
public:
	EventManager(World _world);
	~EventManager();

	/*
	 * Poll SDL_Event to see if any inputs have been pressed
	 * and make the appropriate callback
	 */
	void update(SDL_Event* window_event);

private:
	World world;

	void _fire(std::string key); // Trigger an event
	void _register(); // Register an event
};

} }