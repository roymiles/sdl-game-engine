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

Floor::Floor(int _x, int _y)
{
	x = _x;
	y = _y;
}


Floor::~Floor()
{
}

void Floor::setup()
{
	// Create instances of all components for entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { utilities::resourceFolder + "grass.bmp" });
    spriteComponent->setZIndex(BACKGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(x, y, 100, 100);

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
