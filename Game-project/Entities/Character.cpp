#include "Character.h"
#include "../Utility/FileHelpers.h"

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
	spriteComponent->setImagePath(utilities::resourceFolder + "hi.bmp");

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
