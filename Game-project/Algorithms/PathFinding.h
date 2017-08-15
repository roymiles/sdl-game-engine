#pragma once

#include <vector>

namespace game { namespace algorithms {

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void createNavMesh();

	std::vector<std::vector<int>> navMesh;
};

} }
