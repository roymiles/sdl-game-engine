#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"

namespace game {
namespace entities {

using namespace components;

class Floor : public Entity
{
public:
	Floor(int _x, int _y);
	~Floor();

	void setup() override;
	void update() override;
	const std::string getName() const override;
	int getCurrentState() const override;

private:
	static const std::string name;

	const enum state : int { IDLE, SIZE=1 };
	state currentState;

	int x;
	int y;
};

}
}
