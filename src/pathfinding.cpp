/*
#include "pathfinding.h"

namespace Pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath)
	{
		SquareGrid grid(4, 3);

		for (int row = 0; row < grid.height; row++)
		{
			for (int column = 0; column < grid.width; column++)
			{
				const int map_index{row * grid.width + column};
				const int map_value{Map[map_index]};

				if (map_value == 1)
				{
					grid.walls.insert(GridLocation{column, row});
				}
			}
		}

		return false;
	}
}
*/
