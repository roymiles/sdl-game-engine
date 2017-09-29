#include <iostream> // temp debugging

#include "Character.h"
#include "../Utility/FileHelper.h"
#include "../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;
using namespace algorithms;

const std::string Character::name = "Character";
int Character::movementSpeed = 1 * World::METER; // 1 meter per frame

Character::Character(int _width, int _height)
	: width(_width), height(_height)
{
	currentState = state::IDLE;
}

Character::~Character()
{
}

void Character::setup(int entityId)
{
	//isFollowingPath = false;
	// Register any events

	// Create instances of all the components for this entity

	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { FileHelper::resourceFolder + "character.bmp" });
	//spriteComponent->setImagePaths(state::MOVING, { utilities::resourceFolder + "mega-man-moving.bmp", utilities::resourceFolder + "mega-man.bmp" });
	spriteComponent->setImagePaths(state::MOVING, { FileHelper::resourceFolder + "character.bmp" });
	spriteComponent->setLayer(FOREGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());
	// Drawn in the centre of the screen
	// The rectangles are drawn on screen from the top left of the image
	// To ensure the character is exactly in the middle, the character needs to be offset by its height and width
	transformComponent->setDimensions(WindowManager::WIDTH/2, WindowManager::HEIGHT/2, 100, 100);

	std::shared_ptr<RigidBody> rigidBodyComponent(new RigidBody());
	rigidBodyComponent->mass = 0;

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

	std::shared_ptr<MouseButtonUp>  mouseButtonUpEvent(new MouseButtonUp());
	registerEvent(mouseButtonUpEvent);

	// Call the setup function for all the components
	for(auto const &component : components)
	{
		component.second->setup(entityId);
	}
}

void Character::update()
{
	if (isFollowingPath)
	{
		if (pathIndex == path.size())
		{
			isFollowingPath = false;
			return;
		}

		std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
		Vec2i position = transformComponent->getPosition();
		int width = transformComponent->getWidth();
		int height = transformComponent->getHeight();

		int curMove = path[pathIndex];
		switch (curMove) {
			case UP:
				transformComponent->setDimensions(position.x, position.y - PathFinding::resolution, height, width);
				break;
			case RIGHT:
				transformComponent->setDimensions(position.x + PathFinding::resolution, position.y, height, width);
				break;
			case DOWN:
				transformComponent->setDimensions(position.x, position.y + PathFinding::resolution, height, width);
				break;
			case LEFT:
				transformComponent->setDimensions(position.x - PathFinding::resolution, position.y, height, width);
				break;
		}

		pathIndex++; // Move onto next movement
	}
}

void Character::onEvent(std::shared_ptr<Event> event_ptr)
{
	//std::cout << event_ptr->getName() << " event triggered for " << getName() << std::endl;

	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	Vec2i position = transformComponent->getPosition();
    int width = transformComponent->getWidth();
    int height = transformComponent->getHeight();

	// key is the name of the current event that has been triggered
	std::string key = event_ptr->getName();

	// Remember the coordinate (0,0) starts at the top left. This means that the +ve
	// y axis will be downwards, not upwards
	if (UpKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x, position.y - movementSpeed, height, width);
	}
	else if (RightKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x + movementSpeed, position.y, height, width);
	}
	else if (LeftKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x - movementSpeed, position.y, height, width);
	}
	else if (DownKey::name == key) {
		currentState = state::MOVING;
		transformComponent->setDimensions(position.x, position.y + movementSpeed, height, width);
	}
	else if (KeyUp::name == key) {
		currentState = state::IDLE;
	}
	else if (MouseButtonUp::name == key) {
		std::shared_ptr<MouseButtonUp> mouseButtonUp = std::static_pointer_cast<MouseButtonUp>(event_ptr);

		Vec2i worldCoordinates = World::screenToWorldCoordinates( Vec2i(mouseButtonUp->getX(), mouseButtonUp->getY()) );

		//std::cout << "Released mouse at " << mouseButtonUp->getX() << ", " << mouseButtonUp->getY() << std::endl;
		std::cout << "Released mouse at " << worldCoordinates.x << ", " << worldCoordinates.y << std::endl;
		std::cout << "Currently at " << transformComponent->getX() << ", " << transformComponent->getY() << std::endl;
		std::vector<moves> moveList = PathFinding::astar(transformComponent->getX(), transformComponent->getY(), mouseButtonUp->getX(), mouseButtonUp->getY());

		isFollowingPath = true;
		pathIndex		= 0;
		path			= moveList;
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


void Character::onCollision(maths::Vec2i &collisionVector)
{
	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	Vec2i position = transformComponent->getPosition();
	transformComponent->setPosition(position.x - collisionVector.x, position.y - collisionVector.y);
}

} }
