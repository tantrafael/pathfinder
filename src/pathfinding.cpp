#include "pathfinding.h"
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

		SquareGrid::Location StartLocation{Start.first, Start.second};
		SquareGrid::Location GoalLocation{Target.first, Target.second};

		const int MapLength{MapDimensions.first * MapDimensions.second};
		std::vector<SquareGrid::Location> CameFrom(MapLength);
		std::vector<SquareGrid::CostType> CostSoFar(MapLength);

		AStarSearch(Grid, StartLocation, GoalLocation, Heuristic, CameFrom, CostSoFar);

		DrawGrid(Grid, nullptr, &CameFrom, nullptr, &StartLocation, &GoalLocation);
		std::cout << '\n';

		const std::vector<SquareGrid::Location> Path{ReconstructPath(Grid, StartLocation, GoalLocation, CameFrom)};

		DrawGrid(Grid, nullptr, nullptr, &Path, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, &CostSoFar, nullptr, nullptr, &StartLocation, &GoalLocation);

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
