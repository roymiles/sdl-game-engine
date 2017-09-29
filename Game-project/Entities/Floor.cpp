#include <iostream> // temp debugging

#include "Floor.h"
#include "SDL.h"
#include "../Utility/FileHelper.h"
#include "../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;

const std::string Floor::name = "Floor";

Floor::Floor(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{
}


Floor::~Floor()
{
}

void Floor::setup(int entityId)
{
	// Create instances of all components for entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { FileHelper::resourceFolder + "grass.bmp" });
    spriteComponent->setLayer(BACKGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());

	transformComponent->setDimensions(x, y, h, w);

	// Add components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup(entityId);
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

} }
