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

private:
	static const std::string name;
};

}
}
