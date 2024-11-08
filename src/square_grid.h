#pragma once

#include "Graph.h"
#include <array>
#include <vector>

struct SquareGrid
{
	static std::array<GridLocation, 4> DIRS;
	int width, height;
	std::unordered_set<GridLocation> walls;

	SquareGrid(int width_, int height_);
	bool in_bounds(GridLocation id) const;
	bool passable(GridLocation id) const;
	std::vector<GridLocation> neighbors(GridLocation id) const;
};

struct GridWithWeights : SquareGrid
{
	std::unordered_set<GridLocation> forests;
	GridWithWeights(int w, int h);
	double cost(GridLocation from_node, GridLocation to_node) const;
};
