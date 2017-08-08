#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/RigidBody.h"

namespace game {
namespace entities {

using namespace components;

class Box : public Entity
{
public:
	Box();
	~Box();

	void setup() override;
	void update() override;
	const std::string getName() const override;
	int getCurrentState() const override;

private:
	static const std::string name;

	static const enum state : int { IDLE, SIZE=1 };
	state currentState;
};

}
}
