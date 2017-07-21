#include "Entity.h"

namespace game {

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::registerEvent(Event e)
{
	registeredEvents.push_back(e);
}

std::list<Event> Entity::getRegisteredEvents()
{
	return registeredEvents;
}

}