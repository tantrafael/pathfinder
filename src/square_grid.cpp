#include "square_grid.h"

#include <algorithm>

namespace pathfinding
{
	std::array<SquareGrid::Location, 4> SquareGrid::GridDirections = {
		Location{1, 0}, Location{-1, 0},
		Location{0, -1}, Location{0, 1}
	};

	SquareGrid::SquareGrid(int width, int height) : width(width), height(height)
	{
	}

	bool SquareGrid::Location::operator ==(const Location& other) const
	{
		return x == other.x && y == other.y;
	}

	bool SquareGrid::Location::operator !=(const Location& other) const
	{
		return !(*this == other);
	}

	bool SquareGrid::Location::operator <(const Location& other) const
	{
		return std::tie(x, y) < std::tie(other.x, other.y);
	}

	std::size_t SquareGrid::LocationHash::operator()(const Location& id) const noexcept
	{
		return std::hash<int>()(id.x ^ (id.y << 16));
	}

	bool SquareGrid::within_bounds(Location id) const
	{
		return (0 <= id.x) && (id.x < width) && (0 <= id.y) && (id.y < height);
	}

	bool SquareGrid::passable(Location id) const
	{
		return impassable.find(id) == impassable.end();
	}

	std::vector<SquareGrid::Location> SquareGrid::neighbors(Location id) const
	{
		std::vector<Location> results;

		for (Location grid_direction : GridDirections)
		{
			Location next{id.x + grid_direction.x, id.y + grid_direction.y};

			if (within_bounds(next) && passable(next))
			{
				results.push_back(next);
			}
		}

		// See "Ugly paths" section for an explanation.
		if ((id.x + id.y) % 2 == 0)
		{
			std::reverse(results.begin(), results.end());
		}

		return results;
	}

	double SquareGrid::cost(Location from_node, Location to_node) const
	{
		return 1;
	}
}
