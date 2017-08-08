#pragma once

#include <map>
#include <memory>
#include <typeinfo>

#include "Component.h"
#include "Event.h"
#include "Utility/Random.h"

namespace game {

class Entity
{
public:
	Entity();
	virtual ~Entity() = 0;

	virtual void setup() {}
	virtual void update() {}
	virtual void onEvent(std::string name) {}
	virtual const std::string getName() const = 0;
	virtual int getCurrentState() const = 0;

	template<typename T>
	std::shared_ptr<T> getComponent() {
		for (auto &component : components)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(component.second))
			{
				return ptr;
			}
		}

		return NULL;
	}
	std::string setComponent(std::shared_ptr<Component> c);
	bool hasComponent(std::string key);

	std::string registerEvent(std::shared_ptr<Event> e);
	void deregisterEvent(std::string key);
	std::map<std::string, std::shared_ptr<Event>> getRegisteredEvents();
	bool hasRegisteredEvent(std::string key);

	bool operator==(const Entity &other) const;
	bool operator!=(const Entity &other) const;

protected:
	std::map<std::string, std::shared_ptr<Event>> registeredEvents;
	std::map<std::string, std::shared_ptr<Component>> components;
};

typedef std::shared_ptr<Entity> entityPointer;

}
