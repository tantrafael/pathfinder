#include <iostream>
#include "pathfinding.h"

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
