#include <iostream> // temp debugging

#include "Box.h"
#include "SDL.h"
#include "../Utility/FileHelpers.h"
#include "../EventManager.h"

namespace game {
namespace entities {

using namespace events;

const std::string Box::name = "Box";

Box::Box()
{
}


Box::~Box()
{
}

void Box::setup()
{
	// Create instances of all the components for this entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, { utilities::resourceFolder + "hi.bmp" });
    spriteComponent->setLayer(FOREGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(50, 50, 200, 200);

	std::shared_ptr<RigidBody> rigidBodyComponent(new RigidBody());

	// ... and then add these components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);
	setComponent(rigidBodyComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup();
	}
}

void Box::update()
{

}

const std::string Box::getName() const
{
	return name;
}

int Box::getCurrentState() const
{
	return currentState;
}

}
}
