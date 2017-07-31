#pragma once

#include "../Maths/Vec2.h"

namespace game { namespace components {

using namespace maths;

/*
 * Most entities will have this component. It defines the entities
 * current position in the world and orientation.
 */
class Transform
{
public:
	Transform();
	~Transform();

	Vec2d position;
	Vec2d orientation;
};

} }
