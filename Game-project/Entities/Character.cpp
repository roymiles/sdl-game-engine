#include <iostream> // temp debugging

#include "Character.h"
#include "../Utility/FileHelpers.h"
#include "../Events/KeyUp.h"
#include "../Events/KeyDown.h"
#include "../Maths/Vec2.h"

namespace game { namespace entities {

using namespace events;

const std::string Character::name = "Character"; 

Character::Character()
{
}


Character::~Character()
{
}

void Character::setup()
{
	// Register any events

	// Create instances of all the components for this entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite());
	spriteComponent->setImagePath(utilities::resourceFolder + "hi.bmp");

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(10, 10, 5, 5);

	// ... and then add these components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);

	// Register for any events
	std::shared_ptr<KeyDown> keyDownEvent(new KeyDown());
    std::shared_ptr<KeyUp> keyUpEvent(new KeyUp());
	registerEvent(keyUpEvent);
    registerEvent(keyDownEvent);

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
	std::cout << "Event triggered: " << key << std::endl;

	std::shared_ptr<Transform> transformComponent = getComponent<Transform>();
	Vec2d position = transformComponent->getPosition();
    int width = transformComponent->getWidth();
    int height = transformComponent->getHeight();
    
    transformComponent->setDimensions(position.x, position.y, width+100, height+200);
    
	/*switch (key) {
		case "KEY_UP":
			break;
	}*/
}

const std::string Character::getName() const
{
	return name;
}

} }
