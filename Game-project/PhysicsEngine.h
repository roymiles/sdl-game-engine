#pragma once

#include "World.h"
#include "Entity.h"
#include "Components/RigidBody.h"
#include "WindowManager.h"

namespace game {

/*
 * The game engine is responsible for identifying any potential collisions
 * and resolving them using impulses
 * 1. Using square colliders first then looking into arbitrary manifold meshes
 * 2. Some objects can't move and so need to represent infinite mass
 */
using namespace components;

typedef std::pair<entityPointer, entityPointer> collisionPair;

class PhysicsEngine
{
public:
	PhysicsEngine(std::shared_ptr<World> _world);
	~PhysicsEngine();

	void update();

private:
	std::shared_ptr<World> world;

	/*
	 * This function is responsible for updating the position of every rigidbody
	 * based on their velocities.
	 */
	//void updatePositions(std::map<std::string, entityPointer>& rigidBodies);

	/*
	 * Restrict entities to inside the level
	 * Any temporary entities that exit the level, will need to be removed
	 */
	void boundToMap(entityPointer& A);

	/*
	 * Every object that goes outside of the screen will wrap round to the other side
	 * This will need to be called inside the update() method
	 */
	void boundToWindow(entityPointer& A);

	/*
	 * Apply friction to the object, which slows it down
	 */
	//void applyFriction(std::map<std::string, entityPointer>& rigidBodies);

	/*
	 * Loop through all the entities and return a list of pairs of objects colliding
	 */
	std::vector<collisionPair> collisionPairs;
	std::list<std::pair<entityPointer, entityPointer>> checkCollisions(entityPointer& A);

	/*
	 * From a pair of colliding meshes, add an impulse to each rigidbody
	 */
#pragma message("Not a fan of this function name, ideas?")
	void respondToCollisions();
};

}

