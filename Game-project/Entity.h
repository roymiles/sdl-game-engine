#pragma once

#include <list>
#include <memory>
#include <typeinfo>

#include "Component.h"
#include "Event.h"

namespace game {

class Entity
{
public:
	Entity();
	virtual ~Entity() = 0;

	virtual void setup() {}
	virtual void update() {}
	virtual void onEvent(int eventID) {}
	virtual std::string getName() = 0;

#pragma message("Look up way of exporting templated function body into cpp file")
	template<typename T>
	std::shared_ptr<T> getComponent() {
		for (auto &component : components)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(component))
			{
				return ptr;
			}
		}

#pragma message("Maybe add a null component/entity type? or is that simply bad for performance?")
		return NULL;
	}
	void setComponent(std::shared_ptr<Component> c);

	template<typename T>
	bool hasComponent() {
		for (auto &component : components)
		{
			if (std::dynamic_pointer_cast<T>(component))
			{
				return true;
			}
		}

		return false;
	}

	void registerEvent(std::shared_ptr<Event> e);
	void deregisterEvent(std::shared_ptr<Event> e);
	std::list<std::shared_ptr<Event>> getRegisteredEvents();

	template<typename T>
	bool hasRegisteredEvent()
	{
		for (auto &e : registeredEvents)
		{
			// If event can be cast to type T, then it is of type T
			if (std::dynamic_pointer_cast<T>(e))
			{
				return true;
			}
		}

		return false;
	}

	bool Entity::operator==(const Entity &other) const;
	bool Entity::operator!=(const Entity &other) const;

protected:
	std::list<std::shared_ptr<Event>> registeredEvents;
	std::list<std::shared_ptr<Component>> components;
};

typedef std::shared_ptr<Entity> entityPointer;

}