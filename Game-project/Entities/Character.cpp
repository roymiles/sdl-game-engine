#include <iostream> // temp debugging

#include "Character.h"
#include "../Utility/FileHelpers.h"
#include "../Events/KeyUp.h"

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
	std::shared_ptr<KeyUp> keyUpEvent(new KeyUp());
	registerEvent(keyUpEvent);

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
