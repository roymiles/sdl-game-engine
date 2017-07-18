#pragma once

#include <iostream>
#include <string>

#include "SDL.h"

namespace game { namespace events {

/*
 * This class is used to register and fire events using a container
 * with appropriate callbacks binded to specific inputs
 */
class EventManager
{
public:
	EventManager();
	~EventManager();

	void handle_inputs(SDL_Event* window_event);

private:
	void _fire(std::string key); // Trigger an event
	void _register(); // Register an event
};

} }