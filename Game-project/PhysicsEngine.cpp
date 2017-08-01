#include "PhysicsEngine.h"

namespace game {

PhysicsEngine::PhysicsEngine(std::shared_ptr<World> _world)
{
	world = _world;
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::update()
{
	// Get all entities with RigidBody components
	std::list<entityPointer> colliders;
	colliders = world->getEntitiesWithComponent<RigidBody>();

	// Get the entities that are going t
	std::list<std::pair<entityPointer, entityPointer>> collisionPairs;
	collisionPairs = checkCollisions(colliders);
	
	respondToCollisions(collisionPairs);
}

/*
 * Takes a list of RigidBody Entities and returns an enumeration of all
 * all the entities that are going to collide (in the form of pairs)
 */
std::list<std::pair<entityPointer, entityPointer>> PhysicsEngine::checkCollisions(std::list<entityPointer>& colliders)
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// The collision meshes
	SDL_Rect meshA;
	SDL_Rect meshB;

	/*
	 *	Want to find all pair combinations of entities and don't want to check for
	 *  a collision between A,B and then B,A. For example:
		1.2 1.3 1.4 1.5
		[2.1] 2.3 2.4 2.5
		[3.1][3.2] 3.4 3.5
		[4.1][4.2][4.3] 4.5
		[5.1][5.2][5.3][5.4]
		After every loop, you only need to loop n-1 elements
	*/

	// This is an enumeration of all the possible pair combinations of rigid body entities
	std::list<std::pair<entityPointer, entityPointer>> collisionPairs;

	// Loop through all colliders and check there isnt a collision with any other
	int n = 0;
	for (auto &A : colliders)
	{
		meshA = A->getComponent<RigidBody>()->collisionMesh;

		// Calculate the sides of rect A
		leftA = meshA.x;
		rightA = meshA.x + meshA.w;
		topA = meshA.y;
		bottomA = meshA.y + meshA.h;

		/*
		 * Loop through all the other entities that can collide with A
		 * Though start from the nth element to avoid checking a different permutation of the same pair
		 * - Iterator values are accessed with *it
		 */
		for (auto B = std::next(colliders.begin(), n); B != colliders.end(); ++B) {
		{
			meshB = (*B)->getComponent<RigidBody>()->collisionMesh;

			// Object can't collide with itself
			if (A != (*B))
			{
				// Calculate the sides of rect B
				leftB = meshB.x;
				rightB = meshB.x + meshB.w;
				topB = meshB.y;
				bottomB = meshB.y + meshB.h;

				// If any of the sides from A are outside of B
				if (!(bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB))
					// The two objects are intersecting, collision.
					collisionPairs.push_back(std::make_pair(A, *B));
				}
				
			}
		}

		n++;
	}

	return collisionPairs;
}

/*
 * Applies the appropriate reactive force on the colliding entities
 */
void PhysicsEngine::respondToCollisions(std::list<std::pair<entityPointer, entityPointer>>& collidingPairs)
{
	for (auto &entities : collidingPairs)
	{
		std::shared_ptr<RigidBody> A(entities.first->getComponent<RigidBody>());
		std::shared_ptr<RigidBody> B(entities.second->getComponent<RigidBody>());

#pragma message("Need to double check the entities are referencing same component (no copying)")
		// For now just multiply each rigid bodies velocity by -1 * elasticity
		// Note: Must multiple Vec2 * double (not other way round as not specified in Vec2.h, need to implement)
		A->velocity = A->velocity * A->elasticity * -1.0;
		B->velocity = A->velocity * A->elasticity * -1.0;
	}
}

}
