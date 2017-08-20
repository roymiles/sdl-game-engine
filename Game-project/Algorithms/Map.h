#pragma once

#include "micropather.h"
#include <math.h>
#include <iostream>

using namespace micropather; // Remove at later date

const int MAPX = 30;
const int MAPY = 10;
const char gMap[MAPX*MAPY + 1] =
//"012345678901234567890123456789"
"     |      |                |"
"     |      |----+    |      +"
"---+ +---DD-+      +--+--+    "
"   |                     +-- +"
"        +----+  +---+         "
"---+ +  D    D            |   "
"   | |  +----+    +----+  +--+"
"   D |            |    |      "
"   | +-------+  +-+    |--+   "
"---+                   |     +";

class Map : public Graph
{
public:
	MPVector<void*> path;
	MicroPather* aStar;
	int maxDir;

	std::vector<std::vector<char>> grid;
	int MAPX, MAPY;

	Map(std::vector<std::vector<char>> &_grid) {
		grid = _grid;

		MAPX = _grid.size();
		MAPY = _grid[0].size();

		aStar = new MicroPather(this, MAPX*MAPY, 6);
		maxDir = 4;
	}

	virtual ~Map() {
		delete aStar;
	}

	int Passable(int nx, int ny)
	{
		if (nx >= 0 && nx < MAPX
			&& ny >= 0 && ny < MAPY)
		{
			int index = ny*MAPX + nx;
			//char c = gMap[index];
			char c = grid[nx][ny];
			if (c == ' ' || c == '0')
				return 1; // Passable
			else if (c >= '1' && c <= '9') {
				int val = c - '0';
				MPASSERT(val > 0);
				return val;
			}
		}
		return 0;
	}

	void NodeToXY(void* node, int* x, int* y)
	{
		int index = (int)((intptr_t)node);
		*y = index / MAPX;
		*x = index - *y * MAPX;
	}

	void* XYToNode(int x, int y)
	{
		return (void*)(y*MAPX + x);
	}


	virtual float LeastCostEstimate(void* nodeStart, void* nodeEnd)
	{
		int xStart, yStart, xEnd, yEnd;
		NodeToXY(nodeStart, &xStart, &yStart);
		NodeToXY(nodeEnd, &xEnd, &yEnd);

		int dx = xStart - xEnd;
		int dy = yStart - yEnd;
		return (float)std::sqrt((double)(dx*dx) + (double)(dy*dy));
	}

	virtual void  AdjacentCost(void* node, MPVector< StateCost > *neighbors)
	{
		int x, y;
		//					E  N  W   S     NE  NW  SW SE
		const int dx[8] = { 1, 0, -1, 0,	1, -1, -1, 1 };
		const int dy[8] = { 0, -1, 0, 1,	-1, -1, 1, 1 };
		const float cost[8] = { 1.0f, 1.0f, 1.0f, 1.0f,
			1.41f, 1.41f, 1.41f, 1.41f };

		NodeToXY(node, &x, &y);

		for (int i = 0; i<maxDir; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			int pass = Passable(nx, ny);
			if (pass > 0) {
				// Normal floor
				StateCost nodeCost = { XYToNode(nx, ny), cost[i] * (float)(pass) };
				neighbors->push_back(nodeCost);
			}
		}
	}

	virtual void  PrintStateInfo(void* node)
	{
		int x, y;
		NodeToXY(node, &x, &y);
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}

};