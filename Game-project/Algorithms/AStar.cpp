#include "AStar.h"
#include <math.h>
#include <algorithm>
#include <iostream>

#include "../Utility/Common.h"

namespace game { namespace algorithms {

using namespace utilities;

//#define DEBUG_ASTAR

AStar::AStar(std::vector<std::vector<char>> _grid, int _resolution)
{
	grid		= _grid;
	resolution	= _resolution;

	MAX_X = _grid.size() * _resolution;
	MAX_Y = _grid[0].size() * _resolution;

	closedSet.reserve(_grid.size() * _grid[0].size());
	openSet.reserve(_grid.size() * _grid[0].size());
}

AStar::~AStar()
{
}

bool AStar::calculate(int startX, int startY, int endX, int endY, std::vector<std::shared_ptr<Node>> &path)
{
	// Perhaps these should round down?
	startX = roundUp(startX, resolution);
	startY = roundUp(startY, resolution);
	endX   = roundUp(endX, resolution);
	endY   = roundUp(endY, resolution);

	// Check if start and end coordinates are inside the grid
	// Double check conditions
	//if (!(startX > 0 && startX < MAX_X && startY > 0 && startY < MAX_Y &&
	//	endX > 0 && endX < MAX_X && endY > 0 && endY < MAX_Y)) {
	//	return false;
	//}

	startNode = std::shared_ptr<Node>(new Node(startX, startY));
	endNode   = std::shared_ptr<Node>(new Node(endX, endY));

	openSet.push_back(startNode);
	// Closed set is empty

	startNode->G = 0; // Length of start node to this node
	startNode->F = startNode->G + heuristic(startNode, endNode);

	while (!openSet.empty())
	{
		// Get node with lowest f cost
		std::shared_ptr<Node> current = openSet[0];
		for (int i = 0; i < openSet.size(); i++)
		{
			if (openSet[i]->F < current->F)
			{
				current = openSet[i];
			}
		}

#ifdef DEBUG_ASTAR
		std::cout << "Currently at (" << current->x << "," << current->y << ") => " << current->F << std::endl;
#endif

		if (current->x == endX && current->y == endY)
		{
			path = constructPath(current);
			return true; // Path found
		}

		// Remove current from open list
		removeNode(current);

		// Add current to closed list
		closedSet.push_back(current);

		for (auto &neighbour : getNeighbours(current))
		{
			if (!inClosedList(neighbour->x, neighbour->y))
			{
				neighbour->F = neighbour->G + heuristic(neighbour, endNode);
				if (!inOpenList(neighbour->x, neighbour->y)) {
					// Add neighbour to open list
					openSet.push_back(neighbour);
				}
				else {
					std::shared_ptr<Node> openNeighbour = getNodeInOpenList(neighbour->x, neighbour->y);
					if (neighbour->G < openNeighbour->G)
					{
						openNeighbour->G = neighbour->G;
						openNeighbour->parent = neighbour->parent;
					}
				}
			}
		}

#ifdef DEBUG_ASTAR
		std::cout << "Open set:";
		for (auto const &node : openSet)
		{
			std::cout << "(" << node->x << "," << node->y << ")=" << node->F << " ";
		}
		std::cout << std::endl;
#endif
	}

	return false; // no path exists

}

int AStar::heuristic(std::shared_ptr<Node> &start, std::shared_ptr<Node> &end)
{
	// No diagonal movement
	return std::abs(end->x - start->x) + std::abs(end->y - start->y);
}

void AStar::removeNode(std::shared_ptr<Node> &_node)
{
	for (auto node = openSet.begin(); node != openSet.end(); ++node)
	{
		if (_node->x == (*node)->x && _node->y == (*node)->y)
		{
			// Remove node
			openSet.erase(node);
			break;
		}
	}
}

std::vector<std::shared_ptr<Node>> AStar::getNeighbours(std::shared_ptr<Node> &_node)
{
	std::vector<std::shared_ptr<Node>> neighbours;

	int x, y;
	x = _node->x;
	y = _node->y;

	// indices are the x, y coordinates divided by the resolution
	int x_i, y_i;
	x_i = x / resolution;
	y_i = y / resolution;

	if (x < MAX_X) {
		if (grid[x_i + 1][y_i] = '0') {
			neighbours.push_back(std::make_shared<Node>(Node(x + resolution, y)));
		}
	}

	if (x > 0) {
		if (grid[x_i - 1][y_i] = '0') {
			neighbours.push_back(std::make_shared<Node>(Node(x - resolution, y)));
		}
	}

	if (y < MAX_Y) {
		if (grid[x_i][y_i + 1] = '0') {
			neighbours.push_back(std::make_shared<Node>(Node(x, y + resolution)));
		}
	}

	if (y > 0) {
		if (grid[x_i][y_i - 1] = '0') {
			neighbours.push_back(std::make_shared<Node>(Node(x, y - resolution)));
		}
	}

	// Assign F, G and H
#ifdef DEBUG_ASTAR
	std::cout << "Neighbours of (" << x << "," << y << ") are:" << std::endl;
#endif
	for (auto &neighbour : neighbours)
	{
		neighbour->G = heuristic(neighbour, startNode); // Distance from neighbour to start node
		neighbour->H = heuristic(neighbour, endNode); // Distance from neighbour to end node
		neighbour->F = neighbour->G + neighbour->H; // Estimated cost

		neighbour->parent = _node;

#ifdef DEBUG_ASTAR
		std::cout << "	(" << neighbour->x << "," << neighbour->y << ") => G:" << neighbour->G << ", H:" << neighbour->H << ", F:" << neighbour->F << std::endl;
#endif
	}

	return neighbours;
}

bool AStar::inClosedList(int x, int y)
{
	for (auto const &node : closedSet)
	{
		if (x == node->x && y == node->y)
		{
			return true;
		}
	}

	return false;
}

bool AStar::inOpenList(int x, int y)
{
	for (auto const &node : openSet)
	{
		if (x == node->x && y == node->y)
		{
			return true;
		}
	}

	return false;
}

std::shared_ptr<Node> AStar::getNodeInOpenList(int x, int y)
{
	for (int i = 0; i < openSet.size(); i++)
	{
		if (x == openSet[i]->x && y == openSet[i]->y)
		{
			return openSet[i];
		}
	}

	return nullptr;
}

std::vector<std::shared_ptr<Node>> AStar::constructPath(std::shared_ptr<Node> &_node)
{
	std::vector<std::shared_ptr<Node>> path;
	path.push_back(_node);

#ifdef DEBUG_ASTAR
	std::cout << "Path = (" << _node->x << ", " << _node->y << ")";
#endif
	while (_node->parent != nullptr)
	{
		_node = _node->parent;
		path.push_back(_node);

#ifdef DEBUG_ASTAR
		std::cout << "-> (" << _node->x << ", " << _node->y << ")";
#endif
	}
#ifdef DEBUG_ASTAR
	std::cout << std::endl;
#endif

	// Flip the vector so its start->end rather than end->start
	// std::reverse(path.begin(), path.end());
	return path;
}

} }