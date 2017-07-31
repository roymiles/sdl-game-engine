#pragma once

namespace game {

typedef std::shared_ptr<Component> componentPointer;

class Component
{
public:
	Component();
	~Component();

	virtual void setup() {}
	virtual void update() {}

	bool Component::operator==(const Component &other) const {};
	bool Component::operator!=(const Component &other) const {};
};

}