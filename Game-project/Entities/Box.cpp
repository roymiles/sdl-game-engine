#include <iostream> // temp debugging

#include "Box.h"
#include "SDL.h"
#include "../EventManager.h"

namespace game { namespace entities {

using namespace events;
using namespace utilities;

const std::string Box::name = "Box";

Box::Box(int _x, int _y, int _width, int _height, std::vector<std::string> _idleImagePaths)
		 : x(_x), y(_y), width(_width), height(_height)
{
	idleImagePaths = _idleImagePaths;
}

Box::~Box()
{
}

void Box::setup(int entityId)
{
	// Create instances of all the components for this entity
	std::shared_ptr<Sprite> spriteComponent(new Sprite(state::SIZE));
	spriteComponent->setImagePaths(state::IDLE, idleImagePaths);
    spriteComponent->setLayer(FOREGROUND);

	std::shared_ptr<Transform> transformComponent(new Transform());
	transformComponent->setDimensions(x, y, width, height);

	std::shared_ptr<RigidBody> rigidBodyComponent(new RigidBody());

	// ... and then add these components to the container
	setComponent(spriteComponent);
	setComponent(transformComponent);
	setComponent(rigidBodyComponent);

	// Call the setup function for all the components
	for (auto &component : components)
	{
		component.second->setup(entityId);
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

} }
