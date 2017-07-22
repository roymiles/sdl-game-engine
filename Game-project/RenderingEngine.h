#pragma once

namespace game {

/*
 * This class is responsible for drawing all the entities on screen and in
 * the right order. 
 * 1. Do transparent images appear transparent through SDL?
 * 2. Only draw entities that are within the window
 */
class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void update();
};

}

