#include "Path.h"

#include <string>

#include "../WindowManager.h"

namespace game { namespace entities {

const std::string Path::name = "Path";

Path::Path()
{

}

Path::~Path()
{

}

const std::string Path::getName() const
{
	return name;
}

void Path::setup(int entityId)
{
}

void Path::draw(int cameraX, int cameraY, int cameraWidth, int cameraHeight)
{
	maths::Vec2i prevPoint;
	SDL_SetRenderDrawColor(WindowManager::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < points.size(); i++)
	{
		// Adjust the draw positions so that they move relative to the camera
		points[i].x -= cameraX;
		points[i].y -= cameraY;
		// Make the target of the camera at the centre of the screen
		points[i].x += WindowManager::WIDTH / 2;
		points[i].y += WindowManager::HEIGHT / 2;
		// Offset the camera by the width and height of the target
		// This is because rectangle coordinates are specified by the top left corner rather than the centre
		points[i].x -= cameraWidth / 2;
		points[i].y -= cameraHeight / 2;

		if (i != 0)
		{
			SDL_RenderDrawLine(WindowManager::renderer, prevPoint.x, prevPoint.y, points[i].x, points[i].y);
		}
		prevPoint = points[i];
	}
	SDL_RenderPresent(WindowManager::renderer);
}

} }