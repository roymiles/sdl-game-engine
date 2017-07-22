#pragma once

#include <list>
#include <memory>

#include "Component.h"
#include "Event.h"

namespace game {

class Entity
{
public:
	Entity();
	~Entity();

#pragma message("Do these need to be pure virtual?")
	virtual void setup() {}
	virtual void update() {}
	virtual void onEvent(Event e) {}

#pragma message("Look up way of exporting templated function body into cpp file")
	template<typename T>
	std::shared_ptr<T> getComponent() {
		for (auto &component : components)
		{
#pragma message("Find a better way of doing comparison between objects")
			return NULL;
			//if (std::type_info(T) == std::type_info(component))
			//{
			//	return std::shared_ptr<T>(component);
			//}
		}

#pragma message("Maybe add a null component/entity type? or is that simply bad for performance?")
		return NULL;
	}
	void setComponent(Component c);

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

	void registerEvent(Event e);
	void deregisterEvent(Event e);
	std::list<Event> getRegisteredEvents();
	bool hasRegisteredEvent(Event e);

	bool Entity::operator==(const Entity &other) const;
	bool Entity::operator!=(const Entity &other) const;

private:
	std::list<Event> registeredEvents;
	std::list<Component> components;
};

}