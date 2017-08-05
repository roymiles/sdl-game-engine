//#include "EventManager.h"
//
//namespace game {
//
//EventManager::EventManager(std::shared_ptr<World> _world)
//{
//	world = _world;
//}
//
//
//EventManager::~EventManager()
//{
//}
//
//void EventManager::update(SDL_Event* window_event)
//{
//	if (SDL_PollEvent(window_event)) {
//		switch (window_event->type) {
//			/* Keyboard event */
//			case SDL_KEYDOWN:
//			case SDL_KEYUP:
//				//triggerEvent(KEY_DOWN);
//				break;
//
//				/* SDL_QUIT event (window close) */
//			case SDL_QUIT:
//				//triggerEvent(KEY_DOWN);
//				break;
//
//			default:
//				break;
//		}
//	}
//}
//
//void EventManager::triggerEvent(eventPointer e)
//{
//	for (auto &entity : world->entityContainer)
//	{
//		// Check if this entity has registered for this event
//		if (entity.second->hasRegisteredEvent(e)) {
//			entity.second->onEvent(e);
//		}
//	}
//}
//
//}
