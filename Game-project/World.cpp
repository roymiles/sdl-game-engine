#include "World.h"

// To generate the unique entity keys
#include "Utility/Random.h"

#include <iostream>
#include <sstream>

namespace game {

using namespace utilities;

std::map<std::string, entityPointer> World::entityContainer = {};

World::World()
{
}


World::~World()
{
}

entityPointer World::getEntity(std::string key)
{
	return entityContainer[key];
}

std::vector<std::shared_ptr<Entity>> World::getEntitiesAtPoint(SDL_Point &point)
{
	std::shared_ptr<Transform> transformComponent;
	std::vector<std::shared_ptr<Entity>> entitiesAtPoint;
	for (auto &entity : entityContainer)
	{
		if (entity.second->hasComponent(Transform::name))
		{
			transformComponent = entity.second->getComponent<Transform>();

			// Check if the entity covers the point
			if (SDL_PointInRect(&point, &transformComponent->getRect()))
			{
				entitiesAtPoint.push_back(entity.second);
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
	for (int currentLayer = layers::FOREGROUND; currentLayer >= layers::BACKGROUND; currentLayer--)
	{
		// Check if there is an entity at this point and on this layer
		for (auto const &entity : entities)
		{
			if (entity->getComponent<Sprite>()->getLayer() == currentLayer)
			{
				return entity;
			}
		}
	}

	std::cout << "No entities found on layers below or equal to maxLayer" << std::endl;
	return nullptr;
}

std::string World::createEntity(entityPointer entity)
{
	// Add to container and then return entity

	// Create a random key, this will be the unique key for this entitity
	// May need to check this key does not already exist first!
	std::string randomKey = randomString(7);

	entityContainer[entity->getName() + "_" + randomKey] = entity;

	return randomKey;
}

void World::createEntity(entityPointer entity, std::string key)
{
	// Add to container and then return entity
	entityContainer[entity->getName() + "_" + key] = entity;
}

void World::removeEntity(std::string key)
{
	entityContainer.erase(key);
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

	std::shared_ptr<Character> character(new Character());
	createEntity(character);

	std::shared_ptr<Camera> camera(new Camera(character));
	createEntity(camera);

	std::shared_ptr<Box> box(new Box({ FileHelper::resourceFolder + "crate.bmp" }));
	createEntity(box);
        
	// UI elements
	std::shared_ptr<Button> button(new Button());
	createEntity(button);

	for (int x = 0; x < WindowManager::WIDTH; x += 10)
	{
		std::shared_ptr<Block> block(new Block(x, WindowManager::HEIGHT));

		// Use x key as opposed to a random string
		std::stringstream ss;
		ss << x;

		createEntity(block, ss.str());
	}

	for (int x = 0; x < WindowManager::WIDTH; x += 100)
	{
		for (int y = 0; y < WindowManager::HEIGHT; y += 100)
		{
			std::shared_ptr<Floor> floor(new Floor(x, y));

			// Use x_y key as opposed to a random string
			std::stringstream ss;
			ss << x << "_" << y;

			createEntity(floor, ss.str());
		}
	}
	// ----------------------------------------

	// Loop through all the created entities and call setup
	for (auto &entity : entityContainer)
	{
		// Calling setup on each entity will also internally call
		// setup on each of their components
		entity.second->setup();
	}

	// Override default parameters
	// box->getComponent<Sprite>()->setImagePaths(box->IDLE, { FileHelper::resourceFolder + "box.bmp" });
}

void World::update()
{
	// Loop through all entities and call update
	for (auto &entity : entityContainer)
	{
		entity.second->update();
	}
}

std::map<std::string, entityPointer> World::getEntitiesWithComponent(std::string key)
{
	std::map<std::string, entityPointer> entitiesWithComponent;
	for (auto &entity : entityContainer)
	{
		if (entity.second->hasComponent(key))
		{
			// Add a random key at the end to avoid entities of the same type overwriting
			entitiesWithComponent[entity.second->getName() + "_" + randomString(7)] = entity.second;
		}
	}

	return entitiesWithComponent;
}

}

