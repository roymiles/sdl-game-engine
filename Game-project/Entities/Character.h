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
	void onEvent(std::string key) override;
	const std::string getName() const override;

private:
	static const std::string name;
};

} }
