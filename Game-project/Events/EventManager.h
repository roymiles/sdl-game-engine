#pragma once

#include <iostream>

#include "SDL.h"

namespace game { namespace events {

class EventManager
{
public:
	EventManager();
	~EventManager();

	void handle_inputs(SDL_Event* window_event);
};

} }
