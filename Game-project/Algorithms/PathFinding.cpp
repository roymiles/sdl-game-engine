#include "PathFinding.h"
#include "../World.h"
#include "../Entity.h"
#include "../WindowManager.h"
#include "../LevelManager.h"
#include "../Maths/Vec2.h"
#include "AStar.h"

#define DEBUG_PATHFINDING 1

namespace game { namespace algorithms {

// Initialise navMesh and resolution
grid2D_t PathFinding::navMesh = {};
int PathFinding::resolution   = 1;

PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

/*
 * Creates a navigation mesh for the current level 
 *
 * This function is very slow and computes the navigation mesh for the current level
 * This will need to be pre-computed for every level to reduce runtime computation
 */
grid2D_t PathFinding::createNavMesh(int _resolution)
{	 
	// Currently only generate a screen sized nav mesh
	std::vector<std::shared_ptr<Entity>> entitiesAtPoint;
	SDL_Point point;

	int width  = LevelManager::WIDTH;
	int height = LevelManager::HEIGHT;

	// Resize the matrix to the width and height of the map
	// It is good practice to resize a vector before rather than using push_back
	grid2D_t navMesh;
	navMesh.resize(width / _resolution);
	for (auto &y : navMesh)
	{
		y.resize(height / _resolution);
	}

	std::shared_ptr<Entity> entity;
	// Incrementers for the array indices
	int x, x_i, y, y_i;
	for (x = 0, x_i = 0; x < width; x += _resolution)
	{
		for (y = 0, y_i = 0; y < height; y += _resolution)
		{
			point.x = x;
			point.y = y;
			entitiesAtPoint = World::getEntitiesAtPoint(point);

			// If there is no entity at this point, then assume its walkable
			if (entitiesAtPoint.empty()) {
				navMesh[x_i][y_i] = '0';
				continue; // Move onto next x, y coordinate
			}

			// Of these entities at point x,y get the one on the highest layer
			// Need to do this because obstacles are on a layer above the background
			entity = World::getHighestLayerEntity(entitiesAtPoint, layers::FOREGROUND);
			// If the top layer entity has a rigid body component, then it is unwalkable
			if (entity->hasComponent(RigidBody::name))
			{
				navMesh[x_i][y_i] = 'X';
			}
			else {
				navMesh[x_i][y_i] = '0';
			}

			y_i++;
		}

		x_i++;
	}


	return navMesh;
}

void PathFinding::setCurrentNavMesh(grid2D_t _navMesh)
{
	PathFinding::navMesh = _navMesh;
}

void PathFinding::setResolution(int _resolution)
{
	PathFinding::resolution = _resolution;
}

/*
 * Calculate the path from A to B avoiding obstacles U
 */
std::vector<moves> PathFinding::astar(int startX, int startY, int endX, int endY)
{
	// A*
	AStar *aStar = new AStar(PathFinding::navMesh, PathFinding::resolution);

	std::vector<std::shared_ptr<Node>> path;
	//aStar->calculate(startX, startY, endX, endY, path);
	aStar->calculate(endX, endY, startX, startY, path);

	std::vector<moves> moveList;
	moveList.resize(path.size());
	std::shared_ptr<Node> prevState;

#ifdef DEBUG_PATHFINDING
	SDL_SetRenderDrawColor(WindowManager::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
#endif

	for(int i = 0; i < path.size(); i++)
	{
		if (i == 0) {
			prevState = path[i];
		}
		else {
#ifdef DEBUG_PATHFINDING
			std::cout << "(" << prevState->x << ", " << prevState->y << ") -> (" << path[i]->x << ", " << path[i]->y << ") = ";
			SDL_RenderDrawLine(WindowManager::renderer, prevState->x, prevState->y, path[i]->x, path[i]->y);
#endif
			if (path[i]->x == prevState->x + PathFinding::resolution)
			{
				// Moved right
				std::cout << "RIGHT";
				moveList[i] = moves::RIGHT;
			}
			else if (path[i]->x == prevState->x - PathFinding::resolution)
			{
				// Moved left
				std::cout << "LEFT";
				moveList[i] = moves::LEFT;
			}
			// Increasing y-axis is downward, this is because (0,0) is the top left of the screen
			else if (path[i]->y == prevState->y + PathFinding::resolution)
			{
				// Moved down
				std::cout << "DOWN";
				moveList[i] = moves::DOWN;
			}
			else if (path[i]->y == prevState->y - PathFinding::resolution)
			{
				// Moved up
				std::cout << "UP";
				moveList[i] = moves::UP;
			} 
			else
			{
				std::cout << "X";
				//std::cout << "Unknown link between nodes in path" << std::endl;
			}

			prevState = path[i];
			std::cout << std::endl;
		}
	}

#ifdef DEBUG_PATHFINDING
	SDL_RenderPresent(WindowManager::renderer);
#endif
	return moveList;
}

} }
