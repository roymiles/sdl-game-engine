#pragma once

#include "UI.h"
#include "../../Components/Sprite.h"
#include "../../Components/Transform.h"

namespace game { namespace entities {

using namespace components;

class Button : public UI
{
public:
	Button();
	~Button();

	void setup() override;
	void update() override;
	const std::string getName() const override;
	int getCurrentState() const override;

private:
	static const std::string name;

	const enum state : int { IDLE, HOVER, PRESSED, SIZE = 3 };
	state currentState;
};

} }
