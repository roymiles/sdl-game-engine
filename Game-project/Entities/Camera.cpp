#include "Camera.h"
#include "SDL.h"
#include "../World.h"

namespace game { namespace entities {

const std::string Camera::name = "Camera";

Camera::Camera(int _targetIndex)
{
	targetIndex = _targetIndex;
}

std::shared_ptr<Entity> Camera::getTarget()
{
	//return World::entityContainer[targetIndex];
	return nullptr;
}


Camera::~Camera()
{
}

void Camera::setup(int _entityId)
{
	entityId = _entityId;
	// Create instances of all the components for this entity
	std::shared_ptr<Transform> transformComponent(new Transform());
	//Vec2d characterPosition = character->getComponent<Transform>()->getPosition();
	//transformComponent->setDimensions(characterPosition.x, characterPosition.y, 0, 0);
	transformComponent->setDimensions(0, 0, 0, 0); // Can't access characters transform component as setup() has not been called on character yet

	// ... and then add these components to the container
	setComponent(transformComponent);
}

void Camera::update()
{
	// Set the camera position to the characters position
	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	std::shared_ptr<Entity> target = getTarget();
	Vec2i targetPosition;
	if (target != nullptr) // If empty, dont move the camera
	{
		// Use target position
		targetPosition = target->getComponent<Transform>()->getPosition();
		transformComponent->setPosition(targetPosition);
	}
}

const std::string Camera::getName() const
{
	return name;
}

} }
