#pragma once

#include "../Component.h"

#include "../Maths/Vec2.h"

namespace game { namespace components {

using namespace maths;

/*
 * Most entities will have this component. It defines the entities
 * current position in the world and orientation.
 */
class Transform : public Component
{
public:
	Transform();
	~Transform();

	std::string getName() const override;
	unsigned int getID() const override;

	Vec2d position;
	Vec2d orientation;
private:
	// The unique name/ID of the component
	static const std::string name;
	static const unsigned int ID;
};

} }
