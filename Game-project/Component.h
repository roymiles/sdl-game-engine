#pragma once

namespace game {

class Component
{
public:
	Component();
	~Component();

	bool Component::operator==(const Component &other) const;
	bool Component::operator!=(const Component &other) const;
};

}