#include "pathfinding.h"

#include <cassert>

#include "a_star_search.h"
#include "path_reconstruction.h"
#include "visualization.h"

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath)
{
	const bool IsValidInput{pathfinding::CheckValidInput(Start, Target, Map, MapDimensions, OutPath)};

	if (!IsValidInput)
	{
		OutPath.clear();

		return false;
	}

	pathfinding::SquareGrid Grid(MapDimensions.first, MapDimensions.second);

	pathfinding::ParseMap(Map, Grid);

	const std::vector<pathfinding::SquareGrid::Location> GridPath{
		FindGridPath(Start, Target, MapDimensions, Grid)
	};

	ConstructOutput(Grid, GridPath, OutPath);

	const bool IsValidPath{!OutPath.empty()};

	return IsValidPath;
}

namespace pathfinding
	{
		bool CheckValidInput(std::pair<int, int> Start,
	                     std::pair<int, int> Target,
	                     const std::vector<int>& Map,
	                     std::pair<int, int> MapDimensions,
	                     const std::vector<int>& OutPath)
	{
		const bool IsValidMapDimensions{(MapDimensions.first >= 1) && (MapDimensions.second >= 1)};

		const bool IsValidStart{(0 <= Start.first) && (Start.first < MapDimensions.first)
		                        && (0 <= Start.second) && (Start.second < MapDimensions.second)};

		const bool IsValidTarget{(0 <= Target.first) && (Target.first < MapDimensions.first)
		                         && (0 <= Target.second) && (Target.second < MapDimensions.second)};

		const bool IsMatchingMapDimensions{MapDimensions.first * MapDimensions.second == static_cast<int>(Map.size())};

		const bool IsValidPath{OutPath.empty()};

		const bool IsValidInput{
			IsValidMapDimensions && IsValidStart && IsValidTarget && IsMatchingMapDimensions && IsValidPath
		};

		return IsValidInput;
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
		//std::vector<SquareGrid::Location> CameFrom(MapLength, SquareGrid::Location::Undefined);
		std::vector<SquareGrid::Location> CameFrom(MapLength, SquareGrid::Undefined);
		std::vector<SquareGrid::CostType> CostSoFar(MapLength, 0);

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

		const bool IsNoPath{GridPath.empty()};

		if (IsNoPath)
		{
			return;
		}

		// Exclude start position from the output.
		// When start and goal coincide, GridPath holds only that one location.
		const bool IsCoincidingStartAndGoal{GridPath.size() == 1};
		const int StartIndex{IsCoincidingStartAndGoal ? 0 : 1};
		const int GridPathSize{static_cast<int>(GridPath.size())};

		for (int Index{StartIndex}; Index < GridPathSize; Index++)
		{
			const SquareGrid::Location GridLocation{GridPath[Index]};
			const int MapIndex{Grid.GetMapIndex(GridLocation)};
			OutPath.push_back(MapIndex);
		}
	}
}
