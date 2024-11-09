#include "square_grid.h"

#include <algorithm>

namespace pathfinding
{
	std::array<SquareGrid::Location, 4> SquareGrid::Directions = {
		Location{1, 0}, Location{-1, 0},
		Location{0, -1}, Location{0, 1}
	};

	SquareGrid::SquareGrid(int Width, int Height) : Width(Width), Height(Height)
	{
	}

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

	bool SquareGrid::IsWithinBounds(Location GridLocation) const
	{
		return (0 <= GridLocation.X) && (GridLocation.X < Width) && (0 <= GridLocation.Y) && (GridLocation.Y < Height);
	}

	bool SquareGrid::IsPassable(Location GridLocation) const
	{
		return Impassable.find(GridLocation) == Impassable.end();
	}

	std::vector<SquareGrid::Location> SquareGrid::GetNeighbors(Location GridLocation) const
	{
		std::vector<Location> Neighbors;

		for (const Location Direction : Directions)
		{
			Location AdjacentLocation{GridLocation.X + Direction.X, GridLocation.Y + Direction.Y};

			if (IsWithinBounds(AdjacentLocation) && IsPassable(AdjacentLocation))
			{
				Neighbors.push_back(AdjacentLocation);
			}
		}

		// Simple way to get fairly good-looking paths.
		if ((GridLocation.X + GridLocation.Y) % 2 == 0)
		{
			std::reverse(Neighbors.begin(), Neighbors.end());
		}

		return Neighbors;
	}

	SquareGrid::CostType SquareGrid::GetCost(Location FromLocation, Location ToLocation)
	{
		return 1;
	}
}
