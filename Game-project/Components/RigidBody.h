#pragma once

#include "../Component.h"
#include "../Maths/Vec2.h"
#include "SDL.h"

namespace game { namespace components {

using namespace maths;

/*
 * This component gives an entity mass and velocity. These entities can't be deformed
 * but will collide with other rigid bodies 
 */
class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void setup(int entityId) override;

	const std::string getName() const override;

	// Apply an impulse force in a given direction
	// void impulse(Vec2d direction);

	//Vec2d velocity;
	//double mass;
	// The velocity of an object after a collision is proportional
	// to its velocity before. The constant of proportionality is its elasticity
	//double elasticity;

	// The unique name of the component
	// This needs to be public so that it can be accessed without making
	// an unnecessary instance
	static const std::string name;
};

} }

