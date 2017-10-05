#include "World.h"

// To generate the unique entity keys
#include "Utility/Random.h"

#include "LevelManager.h"
#include "WindowManager.h"
#include "Globals.h"
#include "RenderingEngine.h"

#include <iostream>
#include <sstream>

namespace game {

using namespace utilities;

std::vector<entityPointer> World::entityContainer = {};

std::vector<std::vector<int>> World::spriteEntities(layers::SIZE);
std::vector<std::vector<int>> World::renderUpdateEntities(layers::SIZE);

std::vector<int> World::rigidBodyEntities     = {};
std::vector<int> World::physicsUpdateEntities = {};

void World::serializeEntityContainer(const std::string& fileName)
{
	std::ofstream outFile;
	outFile.open(fileName);

	cereal::JSONOutputArchive oarchive(outFile); // Create an output archive
	oarchive("hi"); // Write the data to the archive
}

World::World()
{
}


World::~World()
{
}

entityPointer World::getEntity(std::string key)
{
	return nullptr;
	//return entityContainer[key];
}

std::vector<std::shared_ptr<Entity>> World::getEntitiesAtPoint(SDL_Point &point)
{
	std::shared_ptr<Transform> transformComponent;
	std::vector<std::shared_ptr<Entity>> entitiesAtPoint;
	for (auto &entity : entityContainer)
	{
		transformComponent = entity->getComponent<Transform>();

		if (transformComponent != nullptr)
		{
			// Check if the entity covers the point
			if (SDL_PointInRect(&point, &transformComponent->getRect()))
			{
				entitiesAtPoint.push_back(entity);
			}
		}
	}

	return entitiesAtPoint;
}

std::shared_ptr<Entity> World::getHighestLayerEntity(std::vector<std::shared_ptr<Entity>> entities, layers maxLayer)
{
	// Go down the layers to find the entity that is visable on the walking layers
	// Anything higher than FOREGROUND is on a menu, affect etc and so they don't affect
	// the navigation mesh
	bool tmp = false;
	std::shared_ptr<Sprite> spriteComponent;
	for (int currentLayer = layers::FOREGROUND; currentLayer >= layers::BACKGROUND; currentLayer--)
	{
		// Check if there is an entity at this point and on this layer
		for (auto const &entity : entities)
		{
			spriteComponent = entity->getComponent<Sprite>();
			if (spriteComponent != nullptr)
			{
				if (entity->getComponent<Sprite>()->getLayer() == currentLayer)
				{
					return entity;
				}
			}
		}
	}

	std::cout << "No entities found on layers below or equal to maxLayer" << std::endl;
	return nullptr;
}

// Returns index in container
int World::createEntity(entityPointer entity)
{
	// Add to container and then return entity

	// Create a random key, this will be the unique key for this entitity
	// May need to check this key does not already exist first!
	std::string randomKey = randomString(7);

	int index = createEntity(entity, randomKey);

	return index;
}

int World::createEntity(entityPointer entity, std::string key)
{
	// Add to container and then return entity
	entity->setKey(entity->getName() + "_" + key);
	int index = entityContainer.size(); // Before push_back because index starts at 0
	entityContainer.push_back(entity);

	return index;
}

void World::removeEntity(std::string key)
{
#pragma message("Implement delete function")
	//entityContainer.erase(key);
}

void World::setup()
{
	// -------------- Temporary ---------------
	// TODO: This needs to be ported over to a LevelManager class
	// Create entities for level


	// Load the first level
	//std::shared_ptr<LevelManager> levelManager(new LevelManager());
	//levelManager->loadLevel()

	currentGameState = gameState::Level1;
	// importEntities(state);

	std::shared_ptr<Character> character(new Character(0.8*METER, 0.8*METER));
	int characterIndex = createEntity(character);

	std::shared_ptr<Camera> camera(new Camera(characterIndex));
	createEntity(camera);

	//std::shared_ptr<Box> box(new Box(METER, METER, { FileHelper::resourceFolder + "crate.bmp" }));
	//createEntity(box);
        
	// UI elements. These are _ABSOLUTE entities
	//std::shared_ptr<Button> button(new Button());
	//createEntity(button);

	/* 
	 * Draw the user interface
	 */
	//int blockWidth = METER;
	//int blockHeight = 2*METER;
	//for (int x = 0; x < SCREEN_WIDTH; x += blockWidth)
	//{
	//	std::shared_ptr<Block> block(new Block(x, SCREEN_HEIGHT - blockHeight, blockWidth, blockHeight));

	//	// Use x key as opposed to a random string
	//	std::stringstream ss;
	//	ss << x;

	//	createEntity(block, ss.str());
	//}

	int blockWidth = METER;
	int blockHeight = METER;
	int floorWidth  = METER;
	int floorHeight = METER;
	for (int x = LevelManager::DIMENSIONS.x; x < LevelManager::DIMENSIONS.w; x += floorWidth)
	{
		for (int y = LevelManager::DIMENSIONS.y; y < LevelManager::DIMENSIONS.h; y += floorHeight)
		{
			std::shared_ptr<Floor> floor(new Floor(x, y, floorWidth, floorHeight));

			// Use x_y key as opposed to a random string
			std::stringstream ss;
			ss << x << "_" << y;

			createEntity(floor, ss.str());

			// Add a block
			if (findnoise2(x, y) <= 0) {
				std::shared_ptr<Box> block(new Box(x, y, blockWidth, blockHeight, { FileHelper::resourceFolder + "crate.bmp" }));
				createEntity(block, ss.str());
			}
		}
	}

	PathFinding::setCurrentNavMesh(PathFinding::createNavMesh());

	// ----------------------------------------

	// Loop through all the created entities and call setup
	for(int id = 0; id < entityContainer.size(); id++)
	{
		// Calling setup on each entity will also internally call
		// setup on each of their components
		entityContainer[id]->setup(id);
	}

	//std::ofstream os("out.cereal", std::ios::binary);
	//cereal::JSONOutputArchive archive(os);
	//archive(entityContainer);
	//serializeEntityContainer("world.txt");
	//FileHelper::abc(entityContainer, "world.txt");

	// Override default parameters
	// box->getComponent<Sprite>()->setImagePaths(box->IDLE, { FileHelper::resourceFolder + "box.bmp" });
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity->update();
	}
}

maths::Vec2i World::screenToWorldCoordinates(maths::Vec2i screenCoordinates)
{
	// Convert the x, y cooordinates of the mouse click to the world coordinates
	// The center of the screen (window::width / 2 , window::height / 2) corresponds to (camera.x, camera.y) in world space
	// e.g. subtract the center screen x, y and then add the camera x, y
	int x, y;
	std::shared_ptr<Transform> cameraTransform = getEntity<Camera>()->getComponent<Transform>();
	x = screenCoordinates.x - (SCREEN_WIDTH / 2) + cameraTransform->getX();
	y = screenCoordinates.y - (SCREEN_HEIGHT / 2) + cameraTransform->getY();

	return Vec2i(x, y);
}

}

