#include <iostream> // temp debugging

#include "Character.h"
#include "../Utility/FileHelper.h"
#include "../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;

const std::string Character::name = "Character"; 

Character::Character()
{
	currentState = state::IDLE;
}

Character::~Character()
{
}

void Character::setup()
{
	// Register any events

	// Create instances of all the components for this entity

	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { FileHelper::resourceFolder + "mega-man.bmp" });
	//spriteComponent->setImagePaths(state::MOVING, { utilities::resourceFolder + "mega-man-moving.bmp", utilities::resourceFolder + "mega-man.bmp" });
	spriteComponent->setImagePaths(state::MOVING, { FileHelper::resourceFolder + "mega-man-moving.bmp" });
	spriteComponent->setLayer(FOREGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());
	// Drawn in the centre of the screen
	// The rectangles are drawn on screen from the top left of the image
	// To ensure the character is exactly in the middle, the character needs to be offset by its height and width
	transformComponent->setDimensions(Window::WIDTH/2, Window::HEIGHT/2, 100, 100);

	std::shared_ptr<RigidBody> rigidBodyComponent(new RigidBody());
	// HACK: Character should not have infinite mass, remember to change the physics engine accordingly
	rigidBodyComponent->mass = -1; // Infinite mass

	// ... and then add these components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);
	setComponent(rigidBodyComponent);

	// Register for any events
	std::shared_ptr<KeyUp>	  keyUpEvent(new KeyUp());
	registerEvent(keyUpEvent);

	std::shared_ptr<UpKey>	  upKeyEvent(new UpKey());
    std::shared_ptr<RightKey> rightKeyEvent(new RightKey());
	std::shared_ptr<DownKey>  downKeyEvent(new DownKey());
	std::shared_ptr<LeftKey>  leftKeyEvent(new LeftKey());
	registerEvent(upKeyEvent);
    registerEvent(rightKeyEvent);
	registerEvent(downKeyEvent);
	registerEvent(leftKeyEvent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup();
	}
}

void Character::update()
{

}

void Character::onEvent(std::string key)
{
	std::cout << key << " event triggered for " << getName() << std::endl;

	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	Vec2d position = transformComponent->getPosition();
    int width = transformComponent->getWidth();
    int height = transformComponent->getHeight();

	// Remember the coordinate (0,0) starts at the top left. This means that the +ve
	// y axis will be downwards, not upwards
	if (UpKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x, position.y-5, height, width);
	}
	else if (RightKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x+5, position.y, height, width);
	}
	else if (LeftKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x-5, position.y, height, width);
	}
	else if (DownKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x, position.y+5, height, width);
	}
	else if (KeyUp::name == key) {
		currentState = state::IDLE;
	}
}

const std::string Character::getName() const
{
	return name;
}

int Character::getCurrentState() const
{
	return currentState;
}


void Character::onCollision(maths::Vec2d &collisionVector)
{
	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	Vec2d position = transformComponent->getPosition();
	transformComponent->setPosition(position.x - collisionVector.x, position.y - collisionVector.y);
}

} }
