#include "square_grid.h"

#include <algorithm>

namespace pathfinding
{
	SquareGrid::Location SquareGrid::Location::Undefined = {-1, -1};

	bool SquareGrid::Location::operator ==(Location Other) const
	{
		return (X == Other.X) && (Y == Other.Y);
	}

	bool SquareGrid::Location::operator !=(Location Other) const
	{
		return !(*this == Other);
	}

	bool SquareGrid::Location::operator <(Location Other) const
	{
		return std::tie(X, Y) < std::tie(Other.X, Other.Y);
	}

	std::size_t SquareGrid::LocationHash::operator()(Location GridLocation) const noexcept
	{
		return std::hash<int>()(GridLocation.X ^ (GridLocation.Y << 16));
	}

	std::array<SquareGrid::Location, 4> SquareGrid::Directions = {
		Location{1, 0}, Location{-1, 0},
		Location{0, -1}, Location{0, 1}
	};

	SquareGrid::SquareGrid(int Width, int Height) : Width(Width), Height(Height)
	{
	}

	bool SquareGrid::IsWithinBounds(Location GridLocation) const
	{
		return (0 <= GridLocation.X) && (GridLocation.X < Width) && (0 <= GridLocation.Y) && (GridLocation.Y < Height);
	}

	bool SquareGrid::IsPassable(Location GridLocation) const
	{
		return Impassable.find(GridLocation) == Impassable.end();
	}

	void SquareGrid::GetNeighbors(Location GridLocation, std::vector<Location>& OutNeighbors) const
	{
		OutNeighbors.clear();

		for (const Location GridDirection : Directions)
		{
			Location AdjacentLocation{GridLocation.X + GridDirection.X, GridLocation.Y + GridDirection.Y};

			if (IsWithinBounds(AdjacentLocation) && IsPassable(AdjacentLocation))
			{
				OutNeighbors.push_back(AdjacentLocation);
			}
		}

		// TODO: Investigate why this makes no difference.
		// Simple way to get fairly good-looking paths.
		if ((GridLocation.X + GridLocation.Y) % 2 == 0)
		{
			std::reverse(OutNeighbors.begin(), OutNeighbors.end());
		}
	}

	SquareGrid::CostType SquareGrid::GetCost(Location FromLocation, Location ToLocation)
	{
		return 1;
	}

	int SquareGrid::GetMapIndex(Location GridLocation) const
	{
		return GridLocation.Y * Width + GridLocation.X;
	}
}
