#include "Camera.h"
#include "SDL.h"

namespace game { namespace entities {

const std::string Camera::name = "Camera";

Camera::Camera(std::shared_ptr<Entity> _target)
{
	target = _target;
}

std::shared_ptr<Entity> Camera::getTarget()
{
	return target;
}


Camera::~Camera()
{
}

void Camera::setup(int entityId)
{
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
	Vec2i targetPosition = target->getComponent<Transform>()->getPosition();

	transformComponent->setPosition(targetPosition);
}

const std::string Camera::getName() const
{
	return name;
}

} }
