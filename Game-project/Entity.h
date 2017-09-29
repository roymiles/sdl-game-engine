#pragma once

#include <map>
#include <memory>
#include <typeinfo>

#include "Component.h"
#include "Event.h"
#include "Utility/Random.h"
#include "Maths/Vec2.h"

#include "Dependancies/cereal/archives/json.hpp"

namespace game {

class Entity
{
public:
	Entity();
	//virtual ~Entity() = 0;
	~Entity();

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive("hello");
	}

	virtual void setup(int id) {}
	virtual void update() {}
	virtual void onEvent(std::shared_ptr<Event> event_ptr) {}
	virtual const std::string getName() const = 0;
	virtual int getCurrentState() const { return -1; };

	// Instead of having entity container as a map, it is stored as a vector
	// and the key is a member variable
	std::string key;
	void setKey(std::string _key)
	{
		key = _key;
	}

	template<typename T>
	std::shared_ptr<T> getComponent() {
		if (components.find(T::name) == components.end()) {
			return nullptr;
		}
		else {
			return std::static_pointer_cast<T>(components[T::name]);
		}
	}

	// This is for if you don't want to downcast (which incurs a performance hit)
	std::shared_ptr<Component> getComponent(std::string name) {
		if (components.find(name) == components.end()) {
			return nullptr;
		}
		else {
			return components[name];
		}
	}

	std::string setComponent(std::shared_ptr<Component> c);

	template<typename T>
	bool hasComponent() {
		if (components.find(T::name) == components.end()) {
			return false;
		}
		else {
			return true;
		}
	}

	std::string registerEvent(std::shared_ptr<Event> e);
	void deregisterEvent(std::string key);
	std::map<std::string, std::shared_ptr<Event>> getRegisteredEvents();
	bool hasRegisteredEvent(std::string key);

	bool operator==(const Entity &other) const;
	bool operator!=(const Entity &other) const;

	virtual void onCollision(maths::Vec2i &collisionVector) {}

	// Can be overriden and allows custom draw commands to be called through
	// the rendering engine on every update
	virtual void draw(int cameraX, int cameraY, int cameraWidth, int cameraHeight) {};

protected:
	std::map<std::string, std::shared_ptr<Event>> registeredEvents;
	std::map<std::string, std::shared_ptr<Component>> components;
};

typedef std::shared_ptr<Entity> entityPointer;

}
