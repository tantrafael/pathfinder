#include "square_grid.h"
#include <algorithm>

std::array<GridLocation, 4> SquareGrid::DIRS = {
	GridLocation{1, 0}, GridLocation{-1, 0},
	GridLocation{0, -1}, GridLocation{0, 1}
};

SquareGrid::SquareGrid(int width_, int height_) : width(width_), height(height_)
{
}

bool SquareGrid::in_bounds(GridLocation id) const
{
	return 0 <= id.x && id.x < width && 0 <= id.y && id.y < height;
}

bool SquareGrid::passable(GridLocation id) const
{
	return walls.find(id) == walls.end();
}

std::vector<GridLocation> SquareGrid::neighbors(GridLocation id) const
{
	std::vector<GridLocation> results;
	for (GridLocation dir : DIRS)
	{
		GridLocation next{id.x + dir.x, id.y + dir.y};
		if (in_bounds(next) && passable(next))
		{
			results.push_back(next);
		}
	}
	if ((id.x + id.y) % 2 == 0)
	{
		std::reverse(results.begin(), results.end());
	}
	return results;
}

GridWithWeights::GridWithWeights(int w, int h) : SquareGrid(w, h)
{
}

double GridWithWeights::cost(GridLocation from_node, GridLocation to_node) const
{
	return forests.find(to_node) != forests.end() ? 5 : 1;
}
