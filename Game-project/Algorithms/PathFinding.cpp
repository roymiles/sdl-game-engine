#include "PathFinding.h"
#include "../World.h"
#include "../Entity.h"
#include "../WindowManager.h"
#include "../LevelManager.h"
#include "../Maths/Vec2.h"
#include "AStar.h"

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
<<<<<<< HEAD
grid2D_t PathFinding::createNavMesh(int _resolution)
{	 
=======
std::vector<std::vector<char>> PathFinding::createNavMesh(int resolution)
{

	
>>>>>>> d94245c4856709fa4ae294789975292bfe5d9d24
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

<<<<<<< HEAD
	std::shared_ptr<Entity> entity;
	// Incrementers for the array indices
	int x, x_i, y, y_i;
	for (x = 0, x_i = 0; x < width; x += _resolution)
=======
	//std::shared_ptr<Entity> entity;
	for (int x = 0; x < width; x++)
>>>>>>> d94245c4856709fa4ae294789975292bfe5d9d24
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
<<<<<<< HEAD
			entity = World::getHighestLayerEntity(entitiesAtPoint, layers::FOREGROUND);

=======
			// entity = world->getHighestLayerEntity(entitiesAtPoint, layers::FOREGROUND);
			std::shared_ptr<Entity> entity =  std::make_unique<Entity>(
			    &(* // Dereference the iterator
			      	std::max_element(entitiesAtPoint.begin(), entitiesAtPoint.end(),
			    	[]( const entitiesAtPoint &a, const entitiesAtPoint &b )
			    	{
					return a->getComponent<Sprite>()->getLayer() < b->getComponent<Sprite>()->getLayer();
			    	})
			     )
			); 
>>>>>>> d94245c4856709fa4ae294789975292bfe5d9d24
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
	aStar->calculate(startX, startY, endX, endY, path);

	std::vector<moves> moveList;
	moveList.resize(path.size());
	std::shared_ptr<Node> prevState;
	for(int i = 0; i < path.size(); i++)
	{
		if (i == 0) {
			prevState = path[i];
		}
		else {
			if (path[i]->x == prevState->x + PathFinding::resolution)
			{
				// Moved right
				moveList[i] = moves::RIGHT;
			}
			else if (path[i]->x == prevState->x - PathFinding::resolution)
			{
				// Moved left
				moveList[i] = moves::LEFT;
			}
			// Increasing y-axis is downward, this is because (0,0) is the top left of the screen
			else if (path[i]->y == prevState->y + PathFinding::resolution)
			{
				// Moved down
				moveList[i] = moves::DOWN;
			}
			else if (path[i]->y == prevState->y - PathFinding::resolution)
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
