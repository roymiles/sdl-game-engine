#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/RigidBody.h"
//#include "../Components/Navigation.h"
#include "../Algorithms/PathFinding.h"

namespace game { namespace entities {

using namespace algorithms;
using namespace components;

class Character : public Entity
{
public:
	Character(int x, int y);
	~Character();

	static int movementSpeed;

	void setup(int entityId) override;
	void update() override;
	void onEvent(std::shared_ptr<Event> event_ptr) override;
	const std::string getName() const override;
	int getCurrentState() const override;

	void onCollision(maths::Vec2i &collisionVector) override;

private:
	static const std::string name;

	int entityId; // Id of entity within entityContainer

	const int width, height;

	int gridMovement; // How much the character has moved for the current movement
	int pathIndex;

	std::vector<moves> moveList; // List of all movement operations
	std::vector<std::shared_ptr<Node>> nodeList; // List of all nodes on the path

	bool isFollowingPath;

	enum state : int { IDLE, MOVING, SIZE=2 };
	state currentState;

	// Current position
	int x;
	int y;
};

} }
