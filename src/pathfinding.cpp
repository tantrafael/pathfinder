#include "pathfinding.h"

#include <cassert>

#include "a_star_search.h"
#include "path_reconstruction.h"
#include "visualization.h"

namespace pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath)
	{
		// TODO: Assert valid input.

		SquareGrid Grid(MapDimensions.first, MapDimensions.second);

		ParseMap(Map, Grid);

		const std::vector<SquareGrid::Location> GridPath{
			FindGridPath(Start, Target, MapDimensions, Grid)
		};

		ConstructOutput(Grid, GridPath, OutPath);

		const bool IsValidPath{!OutPath.empty()};

		return IsValidPath;
	}

	void ParseMap(const std::vector<int>& Map, SquareGrid& OutGrid)
	{
		const size_t MapLength{static_cast<size_t>(OutGrid.Width * OutGrid.Height)};
		const bool IsMatchingDimensions{Map.size() == MapLength};
		assert(IsMatchingDimensions);

		for (int Row{0}; Row < OutGrid.Height; Row++)
		{
			for (int Column{0}; Column < OutGrid.Width; Column++)
			{
				const SquareGrid::Location GridLocation{Column, Row};
				const int MapIndex{OutGrid.GetMapIndex(GridLocation)};
				const int MapValue{Map[MapIndex]};
				const bool IsImpassable{MapValue == 0};

				if (IsImpassable)
				{
					const SquareGrid::Location Location{Column, Row};
					OutGrid.Impassable.insert(Location);
				}
			}
		}
	}

	std::vector<SquareGrid::Location> FindGridPath(std::pair<int, int> Start,
	                                               std::pair<int, int> Target,
	                                               std::pair<int, int> MapDimensions,
	                                               const SquareGrid& Grid)
	{
		SquareGrid::Location StartLocation{Start.first, Start.second};
		SquareGrid::Location GoalLocation{Target.first, Target.second};

		const int MapLength{MapDimensions.first * MapDimensions.second};
		std::vector<SquareGrid::Location> CameFrom(MapLength);
		std::vector<SquareGrid::CostType> CostSoFar(MapLength);

		AStarSearch(Grid, StartLocation, GoalLocation, Heuristic, CameFrom, CostSoFar);

		const std::vector<SquareGrid::Location> GridPath{
			ReconstructPath(Grid, StartLocation, GoalLocation, CameFrom)
		};

		DrawGrid(Grid, nullptr, &CameFrom, nullptr, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, nullptr, nullptr, &GridPath, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, &CostSoFar, nullptr, nullptr, &StartLocation, &GoalLocation);

		return GridPath;
	}

	void ConstructOutput(const SquareGrid& Grid,
	                     const std::vector<SquareGrid::Location>& GridPath,
	                     std::vector<int>& OutPath)
	{
		OutPath.clear();

		for (const SquareGrid::Location GridLocation : GridPath)
		{
			const int MapIndex{Grid.GetMapIndex(GridLocation)};

			OutPath.push_back(MapIndex);
		}

		const bool IsValidPath{!GridPath.empty()};

		// Do not include the start position.
		if (IsValidPath)
		{
			OutPath.erase(OutPath.begin());
		}
	}
}
