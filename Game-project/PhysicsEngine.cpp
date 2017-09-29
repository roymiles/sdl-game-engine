#include <iostream>

#include "PhysicsEngine.h"
#include "EventManager.h" // For triggerEvent
#include "LevelManager.h" // boundToMap

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
	std::vector<entityPointer> rigidBodies = world->getEntitiesWithComponent<RigidBody>();

	boundToMap(rigidBodies);
	//updatePositions(rigidBodies);
	//boundToWindow(rigidBodies);
	//applyFriction(rigidBodies);

	std::list<collisionPair> collisionPairs = checkCollisions(rigidBodies);
	if (!collisionPairs.empty()) {
		respondToCollisions(collisionPairs);
	}
}

//void PhysicsEngine::updatePositions(std::map<std::string, entityPointer>& rigidBodies)
//{
//	for (auto &A : rigidBodies)
//	{
//		std::shared_ptr<RigidBody> rigidBodyComponent = A.second->getComponent<RigidBody>();
//		if (rigidBodyComponent->mass != -1) { // If mass is not infinite
//			std::shared_ptr<Transform> transformComponent = A.second->getComponent<Transform>();
//			Vec2d currentPosition = transformComponent->getPosition();
//			
//			// Add the velocity components to their position
//			transformComponent->setPosition(
//				currentPosition.x + rigidBodyComponent->velocity.x,
//				currentPosition.y + rigidBodyComponent->velocity.y
//			);
//		}
//	}
//}
//

void PhysicsEngine::boundToMap(std::vector<entityPointer>& rigidBodies)
{
	for (auto &A : rigidBodies)
	{
		std::shared_ptr<Transform> transformComponent = A->getComponent<Transform>();
		Vec2i position = transformComponent->getPosition();
		// x-axis
		if (position.x + transformComponent->getWidth() > LevelManager::DIMENSIONS.w)
		{
			// Right hand side of the map
			position.x = LevelManager::DIMENSIONS.w - transformComponent->getWidth();
		}
		else if (position.x < 0)
		{
			// Left hand side of the map
			position.x = 0;
		}

		// y-axis
		if (position.y + transformComponent->getHeight() > LevelManager::DIMENSIONS.h)
		{
			// Bottom of screen
			position.y = LevelManager::DIMENSIONS.h - transformComponent->getHeight();
		}
		else if (position.y < 0)
		{
			// Top of screen
			position.y = 0;
		}

		transformComponent->setPosition(position.x, position.y);
	}
}

void PhysicsEngine::boundToWindow(std::vector<entityPointer>& rigidBodies)
{
	for (auto &A : rigidBodies)
	{
		std::shared_ptr<Transform> transformComponent = A->getComponent<Transform>();
		Vec2i position = transformComponent->getPosition();
		// x-axis
		if (position.x > WindowManager::WIDTH)
		{
			// Right hand side of the screen
			position.x = 0;
		}
		else if (position.x + transformComponent->getWidth() < 0)
		{
			// Left hand side of the screen
			position.x = WindowManager::WIDTH;
		}

		// y-axis
		if (position.y > WindowManager::HEIGHT)
		{
			// Bottom of screen
			position.y = 0;
		}
		else if (position.y + transformComponent->getHeight() < 0)
		{
			// Top of screen
			position.y = WindowManager::HEIGHT;
		}

		transformComponent->setPosition(position.x, position.y);
	}
}

//
//void PhysicsEngine::applyFriction(std::map<std::string, entityPointer>& rigidBodies)
//{
//	for (auto &A : rigidBodies)
//	{
//		std::shared_ptr<RigidBody> rigidBodyComponent = A.second->getComponent<RigidBody>();
//		Vec2d velocity = rigidBodyComponent->velocity;
//
//		if (velocity.length() < 0.5) {
//			rigidBodyComponent->velocity.x = 0;
//			rigidBodyComponent->velocity.y = 0;
//		}
//		else {
//			rigidBodyComponent->velocity = velocity * 0.9;
//		}
//	}
//}

std::list<collisionPair> PhysicsEngine::checkCollisions(std::vector<entityPointer>& colliders)
{
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
	std::list<collisionPair> collisionPairs;

	// Loop through all colliders and check there isnt a collision with any other
	int n = 0;
	for (auto &A : colliders)
	{
		meshA = A->getComponent<Transform>()->getRect();
		/*
		 * Loop through all the other entities that can collide with A
		 * Though start from the nth element to avoid checking a different permutation of the same pair
		 * Note: Iterator values are accessed with *it
		 */
		for (auto B = std::next(colliders.begin(), n); B != colliders.end(); ++B)
		{
			meshB = (*B)->getComponent<Transform>()->getRect();

			// Object can't collide with itself
			if (A != (*B))
			{
				// If any of the sides from A are outside of B
				if (SDL_HasIntersection(&meshA, &meshB))
				{
					// The two objects are intersecting, collision.
					std::cout << A->getName() << " is colliding with " << (*B)->getName() << std::endl;
					collisionPairs.push_back(std::make_pair(A, (*B)));
				}
				
			}
		}

		n++;
	}

	return collisionPairs;
}


void PhysicsEngine::respondToCollisions(std::list<collisionPair>& collidingPairs)
{
	for (auto &entities : collidingPairs)
	{
		std::shared_ptr<Transform> transformComponentA = entities.first->getComponent<Transform>();
		std::shared_ptr<Transform> transformComponentB = entities.second->getComponent<Transform>();

        SDL_Rect rectA = transformComponentA->getRect();
        SDL_Rect rectB = transformComponentB->getRect();
                
		SDL_Rect intersectionResult; // A rect containing the amount of intersection
		SDL_IntersectRect(&rectA, &rectB, &intersectionResult);

		std::shared_ptr<RigidBody> rigidBodyComponentA = entities.first->getComponent<RigidBody>();
		std::shared_ptr<RigidBody> rigidBodyComponentB = entities.second->getComponent<RigidBody>();

		// For now just multiply each rigid bodies velocity by -1 * elasticity
		// Note: Must multiple Vec2 * double (not other way round as not specified in Vec2.h, need to implement)
		//rigidBodyComponentA->velocity = rigidBodyComponentA->velocity * rigidBodyComponentA->elasticity * -1.0;
		//rigidBodyComponentB->velocity = rigidBodyComponentB->velocity * rigidBodyComponentB->elasticity * -1.0;

		// Add a slight impulse proportional to the area of the intersection
		Vec2i positionA = transformComponentA->getPosition();
		Vec2i positionB = transformComponentB->getPosition();

		bool left  = (intersectionResult.x == positionA.x);
		bool right = (intersectionResult.x + intersectionResult.w == positionA.x + transformComponentA->getWidth());
		bool above = (intersectionResult.y == positionA.y);
		bool below = (intersectionResult.y + intersectionResult.h == positionA.y + transformComponentA->getHeight());

		// x-axis
		// Note: I'm not sure why it works this way round, but it does :s
		if ( (left && !(above || below)) || (left && (above || below) && intersectionResult.h > intersectionResult.w) )
		{
			// A is on the left of B
			Vec2i leftCollision(-intersectionResult.w, 0);
			Vec2i rightCollision(intersectionResult.w, 0);
			entities.first->onCollision(leftCollision); // Left
			entities.second->onCollision(rightCollision); // Right
		}
		else if ((right && !(above || below)) || (right && (above || below) && intersectionResult.h > intersectionResult.w)) {
			// A is on the right of B
			Vec2i leftCollision(-intersectionResult.w, 0);
			Vec2i rightCollision(intersectionResult.w, 0);
			entities.first->onCollision(rightCollision); // Right
			entities.second->onCollision(leftCollision); // Left
		}
		// y-axis
		else if ((above && !(left || right)) || (above && (left || right) && intersectionResult.h <= intersectionResult.w))
		{
			// A is above B
			Vec2i aboveCollision(0, -intersectionResult.h);
			Vec2i belowCollision(0, intersectionResult.h);
			entities.first->onCollision(aboveCollision); // Above
			entities.second->onCollision(belowCollision); // Below
		}
		else if ((below && !(left || right)) || (below && (left || right) && intersectionResult.h <= intersectionResult.w)) {
			// A is below B
			Vec2i aboveCollision(0, -intersectionResult.h);
			Vec2i belowCollision(0, intersectionResult.h);
			entities.first->onCollision(belowCollision); // Below
			entities.second->onCollision(aboveCollision); // Above
		}
		else {
			// Object is on a corner
			std::cout << "Unknown collision" << std::endl;
		}
	}
}

}
