#pragma once

#include <list>

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

#pragma message("Implement")
	Component getComponent() {}
	Component setComponent() {}

#pragma message("Look up way of exporting templated function body into cpp file")
	template<typename T>
	bool hasComponent() {
		return true;
	}

	void registerEvent(Event e);
#pragma message("De-register event")
	std::list<Event> getRegisteredEvents();

	bool hasRegisteredEvent(Event e) {
		return true;
	}

private:
	std::list<Event> registeredEvents;
	std::list<Component> components;
};

}

