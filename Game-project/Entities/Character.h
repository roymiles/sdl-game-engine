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
	Character();
	~Character();

	void setup() override;
	void update() override;
	void onEvent(std::shared_ptr<Event> event_ptr) override;
	const std::string getName() const override;
	int getCurrentState() const override;

	void onCollision(maths::Vec2d &collisionVector) override;

private:
	static const std::string name;

	int pathIndex;
	std::vector<moves> path;
	bool isFollowingPath;

	enum state : int { IDLE, MOVING, SIZE=2 };
	state currentState;

	// Current position
	int x;
	int y;
};

} }
