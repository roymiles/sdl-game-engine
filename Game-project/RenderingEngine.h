#pragma once

#include "World.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"

namespace game {

using namespace components;

/*
 * This class is responsible for drawing all the entities on screen and in
 * the right order. 
 * 1. Do transparent images appear transparent through SDL?
 * 2. Only draw entities that are within the window
 */
class RenderingEngine
{
public:
	RenderingEngine(std::shared_ptr<World> _world);
	~RenderingEngine();

	/* 
	 * Called on every frame and draws every entity with a sprite component
	 */
	void update();

private:
	std::shared_ptr<World> world;
	std::shared_ptr<Camera> camera;

	void sort(std::map<std::string, entityPointer>& drawableEntities);
};

}

