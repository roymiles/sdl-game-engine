#include "Entity.h"

namespace game {

Entity::Entity()
{

}

Entity::~Entity()
{
}

void Entity::registerEvent(std::shared_ptr<Event> e)
{
	registeredEvents.push_back(e);
}

void Entity::deregisterEvent(std::shared_ptr<Event> e)
{
	for (auto &e2 : registeredEvents)
	{
		if (e == e2)
		{
			registeredEvents.remove(e2);
			return;
		}
	}

#pragma message("Event didn't exist, return false?")
}

std::list<std::shared_ptr<Event>> Entity::getRegisteredEvents()
{
	return registeredEvents;
}

bool Entity::hasRegisteredEvent(std::shared_ptr<Event> e)
{
	for (auto &e2 : registeredEvents)
	{
		if (e == e2)
		{
			return true;
		}
	}

	return false;
}

void Entity::setComponent(std::shared_ptr<Component> c)
{
	components.push_back(c);
}

bool Entity::operator==(const Entity &other) const
{
	// How to do comparison?
#pragma message("How to perform object equality test?")
	return false;
}

bool Entity::operator!=(const Entity &other) const
{
	// How to do comparison?
	return false;
}

}