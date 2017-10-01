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
	Camera(int _targetId);
	~Camera();

	void setup(int entityId) override;
	void update() override;
	const std::string getName() const override;
	std::shared_ptr<Entity> getTarget();

private:
	static const std::string name;

	int targetIndex;
#pragma message("Why does storing the pointer not work?")
	//std::shared_ptr<Entity> target; // The entity the camera will follow
};

} }
