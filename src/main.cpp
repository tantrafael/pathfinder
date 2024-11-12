#include <vector>

#include "pathfinding.h"

int main()
{
	/*
	// Path
	const std::pair<int, int> Start{0, 0};
	const std::pair<int, int> Target{1, 2};
	const std::vector<int> Map{1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
	const std::pair<int, int> MapDimensions{4, 3};
	*/

	/*
	// No path
	const std::pair<int, int> Start{2, 0};
	const std::pair<int, int> Target{0, 2};
	const std::vector<int> Map{0, 0, 1, 0, 1, 1, 1, 0, 1};
	const std::pair<int, int> MapDimensions{3, 3};
	*/

	// 1 x 1 map
	/*
	const std::pair<int, int> Start{0, 0};
	const std::pair<int, int> Target{0, 0};
	const std::vector<int> Map{1};
	const std::pair<int, int> MapDimensions{1, 1};
	*/

	/*
	const std::pair<int, int> Start{0, 0};
	const std::pair<int, int> Target{0, 0};
	const std::vector<int> Map{};
	const std::pair<int, int> MapDimensions{0, 0};
	*/

	// Larger map
	const std::pair<int, int> Start{8, 7};
	const std::pair<int, int> Target{23, 4};
	//const std::pair<int, int> Start{0, 0};
	//const std::pair<int, int> Target{1, 0};
	//const std::pair<int, int> Start{8, 7};
	//const std::pair<int, int> Target{8, 7};
	const std::vector<int> Map
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	const std::pair<int, int> MapDimensions{30, 15};

	std::vector<int> OutPath{};

	//pathfinding::FindPath(Start, Target, Map, MapDimensions, OutPath);
	FindPath(Start, Target, Map, MapDimensions, OutPath);
}
