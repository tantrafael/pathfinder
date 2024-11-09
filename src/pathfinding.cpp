#include "pathfinding.h"

#include "visualization.h"

namespace pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath)
	{
		SquareGrid grid(MapDimensions.first, MapDimensions.second);

		for (int row = 0; row < grid.height; row++)
		{
			for (int column = 0; column < grid.width; column++)
			{
				const int map_index{row * grid.width + column};
				const int map_value{Map[map_index]};

				if (map_value == 0)
				{
					//grid.impassable.insert(GridLocation{column, row});
					grid.impassable.insert(SquareGrid::GridLocation{column, row});
				}
			}
		}

		//std::unordered_map<GridLocation, GridLocation> came_from;
		//std::unordered_map<SquareGrid::GridLocation, SquareGrid::GridLocation> came_from;
		std::unordered_map<SquareGrid::GridLocation, SquareGrid::GridLocation, SquareGrid::GridLocationHash> came_from;
		//std::unordered_map<GridLocation, double> cost_so_far;
		//std::unordered_map<SquareGrid::GridLocation, double> cost_so_far;
		std::unordered_map<SquareGrid::GridLocation, double, SquareGrid::GridLocationHash> cost_so_far;

		//GridLocation start{Start.first, Start.second};
		SquareGrid::GridLocation start{Start.first, Start.second};
		//GridLocation target{Target.first, Target.second};
		SquareGrid::GridLocation target{Target.first, Target.second};

		a_star_search(grid, start, target, came_from, cost_so_far);

		//std::vector<GridLocation> path = reconstruct_path(start, target, came_from);
		std::vector<SquareGrid::GridLocation> path = reconstruct_path(start, target, came_from);

		draw_grid(grid, nullptr, &came_from, nullptr, &start, &target);
		std::cout << '\n';

		draw_grid(grid, nullptr, nullptr, &path, &start, &target);
		std::cout << '\n';

		draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &target);

		for (auto& location : path)
		{
			const int map_index{location.y * grid.width + location.x};

			OutPath.push_back(map_index);
		}

		const bool isValidPath{path.empty() == false};

		if (isValidPath)
		{
			OutPath.erase(OutPath.begin());
		}

		return isValidPath;
	}
}