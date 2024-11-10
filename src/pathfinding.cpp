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
		SquareGrid Grid(MapDimensions.first, MapDimensions.second);

		// TODO: Parse map in a function.
		for (int Row{0}; Row < Grid.Height; Row++)
		{
			for (int Column{0}; Column < Grid.Width; Column++)
			{
				const SquareGrid::Location GridLocation{Column, Row};
				const int MapIndex{Grid.GetMapIndex(GridLocation)};
				const int MapValue{Map[MapIndex]};
				const bool IsImpassable{MapValue == 0};

				if (IsImpassable)
				{
					const SquareGrid::Location Location{Column, Row};
					Grid.Impassable.insert(Location);
				}
			}
		}

		const int MapLength{MapDimensions.first * MapDimensions.second};

		std::vector<SquareGrid::Location> CameFrom(MapLength);
		std::vector<SquareGrid::CostType> CostSoFar(MapLength);

		SquareGrid::Location StartLocation{Start.first, Start.second};
		SquareGrid::Location GoalLocation{Target.first, Target.second};

		AStarSearch(Grid, StartLocation, GoalLocation, Heuristic, CameFrom, CostSoFar);

		/*
		const std::vector<SquareGrid::Location> Path{
			ReconstructPath(StartLocation, GoalLocation, CameFrom, MapDimensions)
		};
		*/
		const std::vector<SquareGrid::Location> Path{ReconstructPath(Grid, StartLocation, GoalLocation, CameFrom)};

		DrawGrid(Grid, nullptr, &CameFrom, nullptr, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, nullptr, nullptr, &Path, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, &CostSoFar, nullptr, nullptr, &StartLocation, &GoalLocation);

		//for (const SquareGrid::Location GridLocation : Path)
		for (const SquareGrid::Location GridLocation : Path)
		{
			const int MapIndex{Grid.GetMapIndex(GridLocation)};

			OutPath.push_back(MapIndex);
		}

		const bool IsValidPath{!Path.empty()};

		// Do not include the start position.
		if (IsValidPath)
		{
			OutPath.erase(OutPath.begin());
		}

		return IsValidPath;
	}
}
