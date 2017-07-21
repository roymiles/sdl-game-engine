#pragma once

#include "../Entity.h"

namespace game { namespace entities {

class Character : public Entity
{
public:
	Character();
	~Character();

	void setup() override;
	void update() override;
	void onEvent(Event e) override;
};

} }
