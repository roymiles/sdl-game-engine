#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"

namespace game { namespace entities {

using namespace components;

class Character : public Entity
{
public:
	Character();
	~Character();

	void setup() override;
	void update() override;
	void onEvent(std::shared_ptr<Event> e) override;
};

} }
