#pragma once

#include "../World.h"

#include <vector>
#include <memory>

namespace game { namespace algorithms {

enum moves {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class PathFinding
{
public:
	PathFinding(std::shared_ptr<World> _world);
	~PathFinding();

	std::vector<std::vector<char>> createNavMesh(int resolution = 5);

	std::vector<std::vector<int>> navMesh;

	std::vector<moves> astar(std::vector<std::vector<char>> map);

private:
	std::shared_ptr<World> world;
};

} }
