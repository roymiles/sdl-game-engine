#include <iostream> // temp debugging

#include "Floor.h"
#include "SDL.h"
#include "../Utility/FileHelpers.h"
#include "../Maths/Vec2.h"
#include "../EventManager.h"

namespace game {
namespace entities {

using namespace events;

const std::string Floor::name = "Floor";

Floor::Floor()
{
}


Floor::~Floor()
{
}

void Floor::setup()
{
	// Create instances of all components for entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite());
	spriteComponent->resizeImageVectors(state::SIZE);
	spriteComponent->setImagePath(state::IDLE, utilities::resourceFolder + "hi.bmp");
        spriteComponent->setZIndex(0);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(0, 0, 100, 100);

	// Add components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup();
	}
}

void Floor::update()
{

}

const std::string Floor::getName() const
{
	return name;
}

int Floor::getCurrentState() const
{
	return currentState;
}

}
}
