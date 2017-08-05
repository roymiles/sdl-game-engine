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
	virtual void onEvent(std::shared_ptr<Event> e) {}

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

#pragma message("Is this redundant since you can just use getComponent<T>() != nullptr")
	template<typename T>
	bool hasComponent() {
		for (auto &component : components)
		{
			// Find a better way!
			return true;
			//if (std::type_info(T) == std::type_info(component))
			//{
			//	return true;
			//}
		}

		return false;
	}

	void registerEvent(std::shared_ptr<Event> e);
	void deregisterEvent(std::shared_ptr<Event> e);
	std::list<std::shared_ptr<Event>> getRegisteredEvents();
	bool hasRegisteredEvent(std::shared_ptr<Event> e);

	bool Entity::operator==(const Entity &other) const;
	bool Entity::operator!=(const Entity &other) const;

protected:
	std::list<std::shared_ptr<Event>> registeredEvents;
	std::list<std::shared_ptr<Component>> components;
};

typedef std::shared_ptr<Entity> entityPointer;

}