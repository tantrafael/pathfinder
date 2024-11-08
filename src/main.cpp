#include <vector>

#include "pathfinding.h"
#include "grid_initialization.h"

int main()
{
	const std::pair<int, int> Start{0, 0};
	const std::pair<int, int> Target{1, 2};
	const std::vector<int> Map{1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
	const std::pair<int, int> MapDimensions{4, 3};
	/*
	const std::pair<int, int> Start{2, 0};
	const std::pair<int, int> Target{0, 2};
	const std::vector<int> Map{0, 0, 1, 0, 1, 1, 1, 0, 1};
	const std::pair<int, int> MapDimensions{3, 3};
	*/
	std::vector<int> OutPath{};

	pathfinding::FindPath(Start, Target, Map, MapDimensions, OutPath);
}
