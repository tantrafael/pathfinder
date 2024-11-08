#include "square_grid.h"

#include <algorithm>

namespace pathfinding
{
	bool operator ==(GridLocation a, GridLocation b)
	{
		return a.x == b.x && a.y == b.y;
	}

	bool operator !=(GridLocation a, GridLocation b)
	{
		return !(a == b);
	}

	bool operator <(GridLocation a, GridLocation b)
	{
		return std::tie(a.x, a.y) < std::tie(b.x, b.y);
	}

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

		// See "Ugly paths" section for an explanation.
		if ((id.x + id.y) % 2 == 0)
		{
			std::reverse(results.begin(), results.end());
		}

		return results;
	}

	double SquareGrid::cost(GridLocation from_node, GridLocation to_node) const
	{
		return 1;
	}
}
