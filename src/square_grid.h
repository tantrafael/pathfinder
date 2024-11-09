#pragma once

#include <array>
#include <unordered_set>
#include <vector>

namespace pathfinding
{
	struct SquareGrid
	{
		struct Location
		{
			int x, y;

			bool operator ==(const Location& other) const;
			bool operator !=(const Location& other) const;
			bool operator <(const Location& other) const;
		};

		struct LocationHash
		{
			std::size_t operator()(const Location& id) const noexcept;
		};

		typedef double CostType;

		static std::array<Location, 4> GridDirections;
		int width, height;
		std::unordered_set<Location, LocationHash> impassable;

		SquareGrid(int width, int height);
		bool within_bounds(Location id) const;
		bool passable(Location id) const;
		std::vector<Location> neighbors(Location id) const;
		double cost(Location from_node, Location to_node) const;
	};
}
