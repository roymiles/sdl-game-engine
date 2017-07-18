#pragma once

#include "../GameObject.h"

namespace game { namespace entities {

class Character : public GameObject
{
public:
	Character();
	~Character();

	void setup() override;
	void update() override;
};

} }

