#include "Entity.h"

namespace game {

Entity::Entity()
{

}

Entity::~Entity()
{
}

std::string Entity::registerEvent(std::shared_ptr<Event> e)
{
	// Add to container and then return the key
	std::string key = e->getName();
	registeredEvents[key] = e;

	return key;
}

void Entity::deregisterEvent(std::string key)
{
	registeredEvents.erase(key);
}

std::map<std::string, std::shared_ptr<Event>> Entity::getRegisteredEvents()
{
	return registeredEvents;
}

bool Entity::hasRegisteredEvent(std::string key)
{
	if (registeredEvents.find(key) == registeredEvents.end()) {
		// not found
		return false;
	}
	else {
		// found
		return true;
	}
}

std::string Entity::setComponent(std::shared_ptr<Component> c)
{
	// Add to container and then return the key
	std::string key = c->getName();
	components[key] = c;

	return key;
}

bool Entity::hasComponent(std::string key) {
	if (components.find(key) == components.end()) {
		// not found
		return false;
	}
	else {
		// found
		return true;
	}
}

bool Entity::operator==(const Entity &other) const
{
	if (getName() == other.getName()) {
		return true;
	}
	else {
		return false;
	}
}

bool Entity::operator!=(const Entity &other) const
{
	if (getName() != other.getName()) {
		return true;
	}
	else {
		return false;
	}
}

}