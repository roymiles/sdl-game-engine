#include "PathFinding.h"
#include "../World.h"
#include "../Entity.h"
#include "../Window.h"
#include "../Maths/Vec2.h"
#include "AStar.h"

namespace game { namespace algorithms {

PathFinding::PathFinding(std::shared_ptr<World> _world)
{
	world = _world;
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
std::vector<std::vector<char>> PathFinding::createNavMesh(int resolution)
{
	// Currently only generate a screen sized nav mesh
	std::vector<std::shared_ptr<Entity>> entitiesAtPoint;
	SDL_Point point;

	int width = Window::WIDTH / resolution;
	int height = Window::HEIGHT / resolution;

	// Resize the matrix to the width and height of the map
	// It is good practice to resize a vector before rather than using push_back
	std::vector<std::vector<char>> navMesh;
	navMesh.resize(width);
	for (auto &y : navMesh)
	{
		y.resize(height);
	}

	std::shared_ptr<Entity> entity;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			point.x = x * resolution;
			point.y = y * resolution;
			entitiesAtPoint = world->getEntitiesAtPoint(point);

			// Of these entities at point x,y get the one on the highest layer
			// Need to do this because obstacles are on a layer above the background
			entity = world->getHighestLayerEntity(entitiesAtPoint, layers::FOREGROUND);

			// If the top layer entity has a rigid body component, then it is unwalkable
			if (entity->hasComponent("RigidBody"))
			{
				navMesh[x][y] = 'X';
			}
			else {
				navMesh[x][y] = '0';
			}

		}
	}

	return navMesh;
}

/*
 * Calculate the path from A to B avoiding obstacles U
 */
std::vector<moves> PathFinding::astar(std::vector<std::vector<char>> grid)
{
	// A*
	//Map map(grid);

	//MicroPather* pather = new MicroPather(&map); // Although you really should set the default params for your game.

	//micropather::MPVector<void*> path; // A vector of all the states
	//float totalCost = 0;
	//void* startState = (void*)(0 * grid.size() + 0); // 0,0
	//void* endState = (void*)(200 * grid.size() + 0); // 0,200
	//int result = pather->Solve(startState, endState, &path, &totalCost);


	AStar *a = new AStar(grid);

	std::vector<std::shared_ptr<Node>> path;
	a->calculate(0, 0, 10, 10, path);

	std::vector<moves> moveList;
	moveList.resize(path.size());
	std::shared_ptr<Node> prevState;
	for(int i = 0; i < path.size(); i++)
	{
		if (i == 0) {
			prevState = path[i];
		}
		else {
			if (path[i]->x == prevState->x + 1)
			{
				// Moved right
				moveList[i] = moves::RIGHT;
			}
			else if (path[i]->x == prevState->x - 1) 
			{
				// Moved left
				moveList[i] = moves::LEFT;
			}
			// Increasing y-axis is downward, this is because (0,0) is the top left of the screen
			else if (path[i]->y == prevState->y + 1)
			{
				// Moved down
				moveList[i] = moves::DOWN;
			}
			else if (path[i]->y == prevState->y - 1)
			{
				// Moved up
				moveList[i] = moves::UP;
			} 
			else
			{
				std::cout << "Unknown link between nodes in path" << std::endl;
			}
		}
	}
	return moveList;
}

} }
