#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"

namespace game { namespace entities {

using namespace components;

class Character : public Entity
{
public:
	Character();
	~Character();

	void setup() override;
	void update() override;
	void onEvent(int eventID) override;
	std::string getName() override;

private:
	static const std::string name;
};

} }
