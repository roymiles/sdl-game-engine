#include <iostream> // temp debugging
#include <math.h>   // ceil 

#include "Character.h"
#include "../Utility/FileHelper.h"
#include "../EventManager.h"
#include "../RenderingEngine.h"
#include "../Globals.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;
using namespace algorithms;

const std::string Character::name = "Character";
int Character::movementSpeed = std::ceil(10*METER / (double)FPS_TARGET); // 1 meter per frame

Character::Character(int _width, int _height)
	: width(_width), height(_height)
{
	currentState = state::IDLE;
}

Character::~Character()
{
}

void Character::setup(int _entityId)
{
	entityId = _entityId;
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
	transformComponent->setDimensions(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, width, height);

	std::shared_ptr<RigidBody> rigidBodyComponent(new RigidBody());
	//rigidBodyComponent->mass = 0;

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
		component.second->setup(_entityId);
	}
}

void Character::update()
{
	if (isFollowingPath)
	{
		if (pathIndex == moveList.size())
		{
			// Finished movement
			isFollowingPath = false;
			return;
		}

		std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
		Vec2i position = transformComponent->getPosition();
		int width = transformComponent->getWidth();
		int height = transformComponent->getHeight();

		int diagMovementSpeed = floor(movementSpeed * 0.707);
		int curMove = moveList[pathIndex];
		int newX = position.x;
		int newY = position.y;
		bool validMove = true;
		bool diag = false;
		switch (curMove) {
			case UP:
				newY -= movementSpeed;
				gridMovement += movementSpeed;
				break;
			case RIGHT:
				newX += movementSpeed;
				break;
			case DOWN:
				newY += movementSpeed; // y coordinates start at top of screen
				break;
			case LEFT:
				newX -= movementSpeed;
				break;
			case UP_LEFT:
				// Have to move slower along diagonal to ensure equal movement speed in all directions
				newX -= diagMovementSpeed;
				newY -= diagMovementSpeed;
				diag = true;
				break;
			case UP_RIGHT:
				newX += diagMovementSpeed;
				newY -= diagMovementSpeed;
				diag = true;
				break;
			case DOWN_LEFT:
				newX -= diagMovementSpeed;
				newY += diagMovementSpeed;
				diag = true;
				break;
			case DOWN_RIGHT:
				newX += diagMovementSpeed;
				newY += diagMovementSpeed;
				diag = true;
				break;
			default:
				validMove = false;
				break;
		}

		if (validMove)
		{
			transformComponent->setDimensions(newX, newY, height, width);
			World::physicsUpdateEntities.push_back(entityId);

			if (diag) {
				gridMovement += diagMovementSpeed;
			}
			else {
				gridMovement += movementSpeed;
			}
		}

		// If character has finished movement, or it wasnt a valid move in the first place, move onto next
		if ((gridMovement > METER && diag == false) || (gridMovement > METER * 0.707 && diag == true) || !validMove)
		{
			// Once movement is over, force character onto the correct grid square
			transformComponent->setDimensions(nodeList[pathIndex]->x * METER, nodeList[pathIndex]->y * METER, height, width);

			gridMovement = 0;
			pathIndex++; // Move onto next movement
		}
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
	int newX = position.x;
	int newY = position.y;

	if (UpKey::name == key) {
		currentState = state::MOVING;
		newY -= movementSpeed;
	}

	if (RightKey::name == key) {
		currentState = state::MOVING;
		newX += movementSpeed;
	}
	
	if (LeftKey::name == key) {
		currentState = state::MOVING;
		newX -= movementSpeed;
	}
	
	if (DownKey::name == key) {
		currentState = state::MOVING;
		newY += movementSpeed;
	}
	
	if (KeyUp::name == key) {
		currentState = state::IDLE;
	}
	
	if (MouseButtonUp::name == key) {
		std::shared_ptr<MouseButtonUp> mouseButtonUp = std::static_pointer_cast<MouseButtonUp>(event_ptr);

		Vec2i worldCoordinates = World::screenToWorldCoordinates( Vec2i(mouseButtonUp->getX(), mouseButtonUp->getY()) );

		//std::cout << "Released mouse at " << mouseButtonUp->getX() << ", " << mouseButtonUp->getY() << std::endl;
		//std::cout << "Released mouse at " << worldCoordinates.x << ", " << worldCoordinates.y << std::endl;
		//std::cout << "Currently at " << transformComponent->getX() << ", " << transformComponent->getY() << std::endl;

		// So the start position starts at the characters feet
		int startX = transformComponent->getX() + (transformComponent->getWidth() / 2);
		int startY = transformComponent->getY() + (transformComponent->getHeight() / 2);

		Vec2i startGridXY = RenderingEngine::roundScreenCoordinates(startX, startY);
		Vec2i endGridXY   = RenderingEngine::roundScreenCoordinates(mouseButtonUp->getX(), mouseButtonUp->getY());
		RenderingEngine::screenGrid[endGridXY.x][endGridXY.y] = 1; // Mark end coordinate

		moveList = PathFinding::astar(startGridXY.x, startGridXY.y, endGridXY.x, endGridXY.y);
		nodeList = PathFinding::path; // Make a copy of all the nodes in the path

		isFollowingPath = true;
		pathIndex		= 0;
		gridMovement    = 0;
	}

	if (currentState == state::MOVING)
	{
		transformComponent->setDimensions(newX, newY, height, width);
		World::physicsUpdateEntities.push_back(entityId);
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
