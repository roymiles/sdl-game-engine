#pragma once

#include <vector>
#include <memory>

namespace game { namespace algorithms {

struct Node
{
	Node(int _x, int _y)
	{
		x = _x;
		y = _y;

		G = 0;
		H = 0;
		F = 0;

		parent = nullptr;
	}

	// G: The length of the path from the start node to this node.
	// H : The straight - line distance from this node to the end node.
	// F : An estimate of the total distance if taking this route.It’s calculated simply using F = G + H.
	int G, H, F;

	std::shared_ptr<Node> parent;

	int x, y;
};

class AStar
{
public:
	AStar(std::vector<std::vector<char>> _grid);
	~AStar();

	bool calculate(int startX, int startY, int endX, int endY, std::vector<std::shared_ptr<Node>> &path);

	// Predict distance from start to end
	int heuristic(std::shared_ptr<Node> &start, std::shared_ptr<Node> &end);

	void removeNode(std::shared_ptr<Node> &_node);

	std::vector<std::shared_ptr<Node>> getNeighbours(std::shared_ptr<Node> &_node);

	// Return true if in closed list
	bool inClosedList(int x, int y);
	bool inOpenList(int x, int y);

	std::shared_ptr<Node> getNodeInOpenList(int x, int y);

	std::vector<std::shared_ptr<Node>> constructPath(std::shared_ptr<Node> &_node);

private:
	size_t MAX_X, MAX_Y;

	int resolution;

	std::shared_ptr<Node> startNode;
	std::shared_ptr<Node> endNode;

	std::vector<std::shared_ptr<Node>> closedSet; // The set of nodes already evaluated

	// The set of currently discovered nodes that are not evaluated yet.
	// Initially, only the start node is known.
	std::vector<std::shared_ptr<Node>> openSet;

	std::vector<std::vector<char>> grid;
};

} }

