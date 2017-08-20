#include "RenderingEngine.h"
#include "Window.h"

namespace game {

RenderingEngine::RenderingEngine(std::shared_ptr<World> _world)
{
	world = _world;

	camera = world->getEntity<Camera>();
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::update()
{
	std::map<std::string, entityPointer> drawableEntities;
	drawableEntities = world->getEntitiesWithComponent(Sprite::name);
	//sort(drawableEntities);

	// Clear the screen
	SDL_RenderClear(Window::renderer);

	// Draw all entities for each layer in order
	for (int currentLayer = layers::BACKGROUND; currentLayer < layers::SIZE; currentLayer++)
	{
		// Draw all the sprites to the screen
		for (auto &entity : drawableEntities)
		{
			// If this entity is for a different layer skip it
			if (entity.second->getComponent<Sprite>()->getLayer() != currentLayer)
				continue;

			// Every entity is drawn inside a box (rectangle)
			std::shared_ptr<Transform> transform = entity.second->getComponent<Transform>();
			SDL_Rect box = transform->getRect();

			std::shared_ptr<Transform> cameraTransform = camera->getComponent<Transform>();
			std::shared_ptr<Transform> cameraTarget = camera->getTarget()->getComponent<Transform>();
			// The sprites are offset by half the screen width and height, so that the character
			// is in the centre of the screen

			// All screen position are relative to the camera
			box.x -= cameraTransform->getPosition().x;
			box.y -= cameraTransform->getPosition().y;
			// Make the target of the camera at the centre of the screen
			box.x += Window::WIDTH / 2;
			box.y += Window::HEIGHT / 2;
			// Offset the camera by the width and height of the target
			// This is because rectangle coordinates are specified by the top left corner rather than the centre
			box.x -= cameraTarget->getWidth() / 2;
			box.y -= cameraTarget->getHeight() / 2;

			std::shared_ptr<Sprite> sprite = entity.second->getComponent<Sprite>();

			// copy the texture to the rendering context
			SDL_RenderCopy(Window::renderer, sprite->getTexture(entity.second->getCurrentState()), NULL, &box); // The current texture depends on the entities state
		}
	}

	// Flip the backbuffer
	// This means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(Window::renderer);
}

// Sort the container of entities according to their layer in ascending order
void RenderingEngine::sort(std::map<std::string, entityPointer>& drawableEntities)
{
    int i, j, n;
    entityPointer temp;
    n = drawableEntities.size();
    
    std::vector<std::string> entityKeys;
    entityKeys.reserve(n);
    
    for (auto &entity : drawableEntities)
    {
        entityKeys.push_back(entity.first);    
    }
    
    for (i=1; i<n-1; i++)
    {
        for (j=1; i<n-1; i++)
        {
            int elem1 = drawableEntities[entityKeys[i-1]]->getComponent<Sprite>()->getLayer();
            int elem2 = drawableEntities[entityKeys[i]]->getComponent<Sprite>()->getLayer();
       
            if (elem1 < elem2) {
                temp=drawableEntities[entityKeys[j]];
                drawableEntities[entityKeys[j]]=drawableEntities[entityKeys[j+1]];
                drawableEntities[entityKeys[j+1]]=temp;
            }
        }
    }

}

}
