#include "grid_initialization.h"
#include "square_grid.h"

namespace pathfinding
{
	void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2)
	{
		for (int x = x1; x < x2; ++x)
		{
			for (int y = y1; y < y2; ++y)
			{
				grid.Impassable.insert(SquareGrid::Location{x, y});
			}
		}
	}

	SquareGrid make_diagram1()
	{
		SquareGrid grid(30, 15);
		add_rect(grid, 3, 3, 5, 12);
		add_rect(grid, 13, 4, 15, 15);
		add_rect(grid, 21, 0, 23, 7);
		add_rect(grid, 23, 5, 26, 7);
		return grid;
	}
}
