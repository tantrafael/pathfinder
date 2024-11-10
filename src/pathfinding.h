#pragma once

#include <vector>

#include "square_grid.h"

namespace pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath);

	void ParseMap(const std::vector<int>& Map, SquareGrid& OutGrid);

	std::vector<SquareGrid::Location> FindGridPath(std::pair<int, int> Start,
	                                               std::pair<int, int> Target,
	                                               std::pair<int, int> MapDimensions,
	                                               const SquareGrid& Grid);

	void ConstructOutput(const SquareGrid& Grid,
	                     const std::vector<SquareGrid::Location>& GridPath,
	                     std::vector<int>& OutPath);
}
