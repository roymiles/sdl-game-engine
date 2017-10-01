#pragma once

#include <vector>
#include <memory>

namespace game { namespace algorithms {

enum moves : int {
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

	// Uses current navMesh
	static std::vector<moves> astar(int startX, int startY, int endX, int endY);

private:
};

} }
