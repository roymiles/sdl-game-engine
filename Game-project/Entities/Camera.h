#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/RigidBody.h"

namespace game {
namespace entities {

using namespace components;

class Camera : public Entity
{
public:
	Camera(std::shared_ptr<Entity> _target);
	~Camera();

	void setup() override;
	void update() override;
	const std::string getName() const override;
	std::shared_ptr<Entity> getTarget();

private:
	static const std::string name;

	std::shared_ptr<Entity> target; // The entity the camera will follow
};

}
}
