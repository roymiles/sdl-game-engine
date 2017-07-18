#include "EventManager.h"

namespace game { namespace events {

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::handle_inputs(SDL_Event* window_event)
{
	if (SDL_PollEvent(window_event)) {
#pragma message("Not quite sure why i need this intermediate variable")
		SDL_Event e = *window_event;
		switch (e.type) {
			/* Keyboard event */
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				_fire("SDL_KEYUP");
				break;

				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				_fire("SDL_KEYUP");
				break;

			default:
				break;
		}
	}
}

void EventManager::_fire(std::string key)
{

}

void EventManager::_register()
{

}

} }