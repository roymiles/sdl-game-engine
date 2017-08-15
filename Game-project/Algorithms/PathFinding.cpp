#include "PathFinding.h"
#include "../Window.h"
#include "../Maths/Vec2.h"

namespace game { namespace algorithms {

PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::createNavMesh()
{
	// Loop through the map
	// -- Currently only generate a screen sized nav mesh
	for (int x = 0; x < Window::WIDTH; x++)
	{
		for (int y = 0; y < Window::HEIGHT; y++)
		{
			// Get the navigation weight
			//getEntityAtPoint(Vec2)
		}
	}
}

} }
