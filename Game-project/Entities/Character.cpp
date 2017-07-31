#include "Character.h"

namespace game { namespace entities {

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
#pragma message("This should be done through a setter function")
	spriteComponent->imagePath = "C:\\Users\\Roy\\Documents\\Game-project\\Game-project\\Resources\\character.png";

	// ... and then add these components to the container
	setComponent(spriteComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component->setup();
	}
}

void Character::update()
{

}

void Character::onEvent(std::shared_ptr<Event> e)
{
	/*switch (key) {
		case "KEY_UP":
			break;
	}*/
}

} }
