#include "Block.h"

#include "../../Utility/FileHelper.h"
#include "../../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;

const std::string Block::name = "Block";

Block::Block(int _x, int _y)
{
	x = _x;
	y = _y;
}


Block::~Block()
{
}

void Block::setup()
{
	// Create instances of all the components for this entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { FileHelper::resourceFolder + "ui-bar.bmp" });
	spriteComponent->setLayer(GUI);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(x, y, 10, 40);
	transformComponent->setDisplayType(_STATIC);

	// ... and then add these components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup();
	}
}

void Block::update()
{

}

const std::string Block::getName() const
{
	return name;
}

int Block::getCurrentState() const
{
	return currentState;
}

} }
