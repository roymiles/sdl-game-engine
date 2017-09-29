#include "RenderingEngine.h"
#include "WindowManager.h"

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

#ifdef DEBUG_TIME
	auto t2 = Clock::now();
#endif

	// Clear the screen
	SDL_RenderClear(WindowManager::renderer);

	std::shared_ptr<Transform> cameraTransform = camera->getComponent<Transform>();
	std::shared_ptr<Transform> cameraTarget    = camera->getTarget()->getComponent<Transform>();
	std::shared_ptr<Entity> entity;

	// Get these values outside the loop
	Vec2i cameraPos  = cameraTransform->getPosition();
	int cameraX      = cameraPos.x;
	int cameraY      = cameraPos.y;
	int cameraWidth  = cameraTarget->getWidth();
	int cameraHeight = cameraTarget->getHeight();

	// Draw all entities for each layer in order
	for (int currentLayer = layers::BACKGROUND; currentLayer < layers::SIZE; currentLayer++)
	{
		// Draw all the sprites to the screen
		for (int i = 0; i < World::renderUpdateEntities[currentLayer].size(); i++)
		{
			// Use the ID as input for the entity container
			entity = World::entityContainer[World::renderUpdateEntities[currentLayer][i]];

			// Every entity is drawn inside a box (rectangle)
			//std::shared_ptr<Component> transform = entity->getComponent(Transform::name);
			std::shared_ptr<Transform> transform = entity->getComponent<Transform>();
			SDL_Rect box = transform->getRect();

			// The sprites are offset by half the screen width and height, so that the character
			// is in the centre of the screen

			if (transform->getDisplayType() == _ABSOLUTE)
			{
				// ---- DRAW RELATIVE TO CAMERA ----
				// All screen position are relative to the camera
				box.x -= cameraX;
				box.y -= cameraY;
				// Make the target of the camera at the centre of the screen
				box.x += WindowManager::WIDTH / 2;
				box.y += WindowManager::HEIGHT / 2;
				// Offset the camera by the width and height of the target
				// This is because rectangle coordinates are specified by the top left corner rather than the centre
				box.x -= cameraWidth / 2;
				box.y -= cameraHeight / 2;
			}

			// Check if the entity is off the screen. If it is, don't render it
			if (box.x + box.w > 0 && box.x < WindowManager::WIDTH && box.y + box.h > 0 && box.y < WindowManager::HEIGHT)
			{
				// The entity is on the screen
				std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

				// copy the texture to the rendering context
				SDL_RenderCopy(WindowManager::renderer, sprite->getTexture(entity->getCurrentState()), NULL, &box); // The current texture depends on the entities state
			}
		}	
	}

	SDL_RenderPresent(WindowManager::renderer);

#ifdef DEBUG_TIME
	auto t3 = Clock::now();
	std::cout << "RenderingEngine:		loop: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count()
		<< " milliseconds" << std::endl;
#endif;

	// Call the draw function for every entity
	// *this function may or may not be overriden from Entity.h*
	for (auto const &e : world->entityContainer)
	{
		e->draw(cameraX, cameraY, cameraWidth, cameraHeight);
	}

	// Flip the backbuffer
	// This means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(WindowManager::renderer);
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
