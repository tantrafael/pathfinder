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

		for (int Row{0}; Row < Grid.Height; Row++)
		{
			for (int Column{0}; Column < Grid.Width; Column++)
			{
				const int MapIndex{Row * Grid.Width + Column};
				const int MapValue{Map[MapIndex]};
				const bool IsImpassable{MapValue == 0};

				if (IsImpassable)
				{
					const SquareGrid::Location Location{Row, Column};
					Grid.Impassable.insert(Location);
				}
			}
		}

		std::unordered_map<SquareGrid::Location, SquareGrid::Location, SquareGrid::LocationHash> CameFrom;
		std::unordered_map<SquareGrid::Location, SquareGrid::CostType, SquareGrid::LocationHash> CostSoFar;

		SquareGrid::Location StartLocation{Start.first, Start.second};
		SquareGrid::Location GoalLocation{Target.first, Target.second};

		AStarSearch(Grid, StartLocation, GoalLocation, Heuristic, CameFrom, CostSoFar);

		const std::vector<SquareGrid::Location> Path{ReconstructPath(StartLocation, GoalLocation, CameFrom)};

		DrawGrid(Grid, nullptr, &CameFrom, nullptr, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, nullptr, nullptr, &Path, &StartLocation, &GoalLocation);
		std::cout << '\n';

		DrawGrid(Grid, &CostSoFar, nullptr, nullptr, &StartLocation, &GoalLocation);

		for (auto& location : Path)
		{
			const int map_index{location.Y * Grid.Width + location.X};

			OutPath.push_back(map_index);
		}

		const bool isValidPath{Path.empty() == false};

		// Do not include start position.
		if (isValidPath)
		{
			OutPath.erase(OutPath.begin());
		}

		return isValidPath;
	}
}
