#include "RenderingEngine.h"
#include "WindowManager.h"
#include "Globals.h"

namespace game {

std::vector<std::vector<int>> RenderingEngine::screenGrid(GRID_COLS, std::vector<int>(GRID_ROWS, 0));

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
	std::shared_ptr<Entity> cameraTarget = camera->getTarget();
	std::shared_ptr<Transform> cameraTargetTransform;
	if (cameraTarget == nullptr)
	{
		// No camera target
		cameraTargetTransform = cameraTransform; // Keep it constant
	}
	else {
		cameraTargetTransform = cameraTarget->getComponent<Transform>();
	}

	std::shared_ptr<Entity> entity;

	// Get these values outside the loop
	Vec2i cameraPos  = cameraTransform->getPosition();
	int cameraX      = cameraPos.x;
	int cameraY      = cameraPos.y;
	int cameraWidth  = cameraTargetTransform->getWidth();
	int cameraHeight = cameraTargetTransform->getHeight();

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

			// EVERYTHING IS STATIC TO SCREEN NOW
			//if (transform->getDisplayType() == _ABSOLUTE)
			//{
			//	// ---- DRAW RELATIVE TO CAMERA ----
			//	// All screen position are relative to the camera
			//	box.x -= cameraX;
			//	box.y -= cameraY;
			//	// Make the target of the camera at the centre of the screen
			//	box.x += SCREEN_WIDTH / 2;
			//	box.y += SCREEN_HEIGHT / 2;
			//	// Offset the camera by the width and height of the target
			//	// This is because rectangle coordinates are specified by the top left corner rather than the centre
			//	box.x -= cameraWidth / 2;
			//	box.y -= cameraHeight / 2;
			//}

			// Check if the entity is off the screen. If it is, don't render it
			if (box.x + box.w > 0 && box.x < SCREEN_WIDTH && box.y + box.h > 0 && box.y < SCREEN_HEIGHT)
			{
				// The entity is on the screen
				std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

				// copy the texture to the rendering context
				SDL_RenderCopy(WindowManager::renderer, sprite->getTexture(entity->getCurrentState()), NULL, &box); // The current texture depends on the entities state
			}
		}	
	}

	// Draw unit square around the character and across the whole screen (fence post problem
	SDL_Rect r;
	r.w = METER;
	r.h = METER;
	for (int i = 0; i < GRID_COLS; ++i)
	{
		for (int j = 0; j < GRID_ROWS; ++j)
		{
			r.x = i * METER;
			r.y = j * METER;

			if (RenderingEngine::screenGrid[i][j] == 1)
			{
				SDL_SetRenderDrawColor(WindowManager::renderer, 255, 255, 255, 122);
				SDL_RenderFillRect(WindowManager::renderer, &r);
			}
			else if (RenderingEngine::screenGrid[i][j] == 2) {
				SDL_SetRenderDrawColor(WindowManager::renderer, 0, 255, 255, 122);
				SDL_RenderFillRect(WindowManager::renderer, &r);
			}
			else if (RenderingEngine::screenGrid[i][j] == 3) {
				SDL_SetRenderDrawColor(WindowManager::renderer, 255, 0, 255, 122);
				SDL_RenderFillRect(WindowManager::renderer, &r);
			}
			else if (RenderingEngine::screenGrid[i][j] == 4) {
				SDL_SetRenderDrawColor(WindowManager::renderer, 255, 255, 0, 122);
				SDL_RenderFillRect(WindowManager::renderer, &r);
			}
			else {
				SDL_SetRenderDrawColor(WindowManager::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(WindowManager::renderer, &r);
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

Vec2i RenderingEngine::roundScreenCoordinates(int _x, int _y)
{
	int x = ((_x + METER / 2) / METER);
	int y = ((_y + METER / 2) / METER);

	return Vec2i(x, y);
}

}
