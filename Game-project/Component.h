#pragma once

#include <memory>
#include <string>

#include "Utility/Common.h"

namespace game {

class Component
{
public:
	Component();
	virtual ~Component() = 0;

	virtual std::string getName() const = 0;
	virtual unsigned int getID()  const = 0;

	virtual void setup() {}
	virtual void update() {}

	//bool Component::operator==(const Component &other) const {};
	//bool Component::operator!=(const Component &other) const {};
};

typedef std::unique_ptr<Component> componentPointer;

}