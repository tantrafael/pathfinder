//#include <iostream>
//#include "pathfinding.h"

/*
int main()
{
	const std::pair<int, int> Start{0, 0};
	const std::pair<int, int> Target{1, 2};
	const std::vector<int> Map{1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
	const std::pair<int, int> MapDimensions{4, 3};
	std::vector<int> OutPath{};

	const bool PathfindingResult
	{
		Pathfinding::FindPath(Start, Target, Map, MapDimensions, OutPath)
	};
}
*/

#include <unordered_map>
#include <vector>

#include "pathfinding.h"
#include "grid_initialization.h"
#include "visualization.h"

int main() {
	GridWithWeights grid = make_diagram4();

	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;

	GridLocation start{1, 4};
	GridLocation goal{8, 3};

	a_star_search(grid, start, goal, came_from, cost_so_far);

	draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
	std::cout << '\n';

	std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
	draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
	std::cout << '\n';

	draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}
