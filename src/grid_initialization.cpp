#include "grid_initialization.h"
#include "square_grid.h"   // For add_rect and GridWithWeights

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2)
{
	for (int x = x1; x < x2; ++x)
	{
		for (int y = y1; y < y2; ++y)
		{
			grid.walls.insert(GridLocation{x, y});
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

GridWithWeights make_diagram4()
{
	GridWithWeights grid(10, 10);
	add_rect(grid, 1, 7, 4, 9);
	grid.forests = std::unordered_set<GridLocation>{
		{3, 4}, {3, 5}, {4, 1}, {4, 2},
		{4, 3}, {4, 4}, {4, 5}, {4, 6},
		{4, 7}, {4, 8}, {5, 1}, {5, 2},
		{5, 3}, {5, 4}, {5, 5}, {5, 6},
		{5, 7}, {5, 8}, {6, 2}, {6, 3},
		{6, 4}, {6, 5}, {6, 6}, {6, 7},
		{7, 3}, {7, 4}, {7, 5}
	};
	return grid;
}
