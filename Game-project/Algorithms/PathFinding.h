#pragma once

#include <vector>
#include <memory>

#include "AStar.h"

namespace game { namespace algorithms {

enum moves : int {
	IDLE, 

	UP,
	DOWN,
	LEFT,
	RIGHT,

	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

typedef std::vector<std::vector<char>> grid2D_t;

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	/* 
	 * Create navigation mesh for the entire level
	 */
	static grid2D_t createNavMesh();

	static void setCurrentNavMesh(grid2D_t _navMesh);
	static void setResolution(int _resolution);

	static int resolution;
	static grid2D_t navMesh;

	static std::vector<std::shared_ptr<Node>> path; // List of all nodes in the path

	// Uses current navMesh
	static std::vector<moves> astar(int startX, int startY, int endX, int endY);

private:
};

} }
