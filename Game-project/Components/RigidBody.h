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
#pragma message("This needs to be changed to an arbitrary mesh")
	RigidBody(SDL_Rect _collisionMesh);
	~RigidBody();

#pragma message("Implement impulse function")
	// Apply an impulse force in a given direction
	void impulse(Vec2d direction);

#pragma message("These should be private, use getters and setters")
	Vec2d velocity;
	double mass;
	// The velocity of an object after a collision is proportional
	// to its velocity before. The constant of proportionality is its elasticity
	double elasticity;

	SDL_Rect collisionMesh;
};

} }

