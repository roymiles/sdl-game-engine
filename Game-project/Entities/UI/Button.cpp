#include "Button.h"

#include "../../Utility/FileHelper.h"
#include "../../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;

const std::string Button::name = "Button";

Button::Button()
{
}


Button::~Button()
{
}

void Button::setup()
{
	// Create instances of all the components for this entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { FileHelper::resourceFolder + "empty.bmp" });
	spriteComponent->setLayer(GUI);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(50, 50, 200, 200);
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

void Button::update()
{

}

const std::string Button::getName() const
{
	return name;
}

int Button::getCurrentState() const
{
	return currentState;
}

} }
