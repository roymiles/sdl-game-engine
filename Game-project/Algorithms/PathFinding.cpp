#include "PathFinding.h"
#include "../World.h"
#include "../Entity.h"
#include "../WindowManager.h"
#include "../LevelManager.h"
#include "../Maths/Vec2.h"
#include "../Entities/Path.h" // Draw paths to screen
#include "../World.h" // createEntity
#include "AStar.h"

// bitset
#include <bitset>

//#define DEBUG_PATHFINDING 0

namespace game { namespace algorithms {

// Initialise navMesh and resolution
grid2D_t PathFinding::navMesh = {};
int PathFinding::resolution   = Character::movementSpeed;

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
grid2D_t PathFinding::createNavMesh()
{	 
	// Currently only generate a screen sized nav mesh
	std::vector<std::shared_ptr<Entity>> entitiesAtPoint;
	SDL_Point point;

	int width  = LevelManager::DIMENSIONS.w;
	int height = LevelManager::DIMENSIONS.h;

	// Resize the matrix to the width and height of the map
	// It is good practice to resize a vector before rather than using push_back
	grid2D_t navMesh(width / resolution);
	//navMesh.resize(width / resolution);
	for (auto &y : navMesh)
	{
		y.resize(height / resolution);
	}

	std::shared_ptr<Entity> entity;
	// Incrementers for the array indices
	int x, x_i, y, y_i;
	for (x = 0, x_i = 0; x < width; x += resolution)
	{
		for (y = 0, y_i = 0; y < height; y += resolution)
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
			if (entity->hasComponent<RigidBody>())
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

	std::shared_ptr<Path> pathEntity(new Path());
	pathEntity->points.resize(path.size());

	for(int i = 0; i < path.size(); i++)
	{
		pathEntity->points[i] = maths::Vec2i(path[i]->x, path[i]->y);

		if (i == 0) {
			prevState = path[i];
		}
		else {
#ifdef DEBUG_PATHFINDING
			std::cout << "(" << prevState->x << ", " << prevState->y << ") -> (" << path[i]->x << ", " << path[i]->y << ") = ";
			SDL_RenderDrawLine(WindowManager::renderer, prevState->x, prevState->y, path[i]->x, path[i]->y);
#endif
			// 4 possible conditions for up, left, down and right
			std::bitset<4> conditions;

			conditions[0] = (path[i]->x == prevState->x + PathFinding::resolution); // right
			conditions[1] = (path[i]->x == prevState->x - PathFinding::resolution); // left

			// Increasing y-axis is downward, this is because (0,0) is the top left of the screen
			conditions[2] = (path[i]->y == prevState->y + PathFinding::resolution); // down
			conditions[3] = (path[i]->y == prevState->y - PathFinding::resolution); // up

			int comparitor = (int)(conditions.to_ulong()); // cast to int so a switch statement can be used
			switch (comparitor)
			{
			case 8:
				// Right
				std::cout << "RIGHT";
				moveList[i] = moves::RIGHT;
				break;
			case 4:
				// Left
				std::cout << "LEFT";
				moveList[i] = moves::LEFT;
				break;
			case 2:
				// Down
				std::cout << "DOWN";
				moveList[i] = moves::DOWN;
				break;
			case 1:
				// Up
				std::cout << "UP";
				moveList[i] = moves::UP;
				break;

				// Diagonal movements are a combination of the above
			case 9:
				// Right + Up
				std::cout << "Up Right";
				moveList[i] = moves::UP_RIGHT;
				break;
			case 5:
				// Left + Up
				std::cout << "Up Left";
				moveList[i] = moves::UP_LEFT;
				break;
			case 10:
				// Right + Down
				std::cout << "Down Right";
				moveList[i] = moves::DOWN_RIGHT;
				break;
			case 6:
				// Right + Down
				std::cout << "Down Left";
				moveList[i] = moves::DOWN_LEFT;
				break;
			}

			prevState = path[i];
			std::cout << std::endl;
		}
	}

	World::createEntity(pathEntity);

#ifdef DEBUG_PATHFINDING
	SDL_RenderPresent(WindowManager::renderer);
#endif
	return moveList;
}

} }
