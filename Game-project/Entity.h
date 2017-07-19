#pragma once

#include <vector>
#include <string>

namespace game {

class Entity
{
public:
	Entity();
	~Entity();

#pragma message("Do these need to be pure virtual?")
	virtual void setup() = 0;
	virtual void update();
	virtual void onEvent(std::string key);

	virtual Component getComponent();
	Component setComponent() {}

	std::vector<Component> components;
};

}

