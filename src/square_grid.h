#pragma once

#include <array>
#include <unordered_set>
#include <vector>

//#include "grid_location_hash.h"

/*
namespace pathfinding
{
	struct GridLocation
	{
		int x, y;
	};
}

namespace std
{
	template <>
	struct hash<pathfinding::GridLocation>
	{
		std::size_t operator()(const pathfinding::GridLocation& id) const noexcept
		{
			return std::hash<int>()(id.x ^ (id.y << 16));
		}
	};
}
*/

namespace pathfinding
{
	/*
	bool operator ==(GridLocation a, GridLocation b);
	bool operator !=(GridLocation a, GridLocation b);
	bool operator <(GridLocation a, GridLocation b);
	*/

	struct SquareGrid
	{
		struct GridLocation
		{
			int x, y;

			bool operator ==(const GridLocation& other) const;
			bool operator !=(const GridLocation& other) const;
			bool operator <(const GridLocation& other) const;
		};

		struct GridLocationHash
		{
			std::size_t operator()(const GridLocation& id) const noexcept;
		};

		static std::array<GridLocation, 4> GridDirections;
		int width, height;
		//std::unordered_set<GridLocation> impassable;
		std::unordered_set<GridLocation, GridLocationHash> impassable;

		SquareGrid(int width, int height);
		bool within_bounds(GridLocation id) const;
		bool passable(GridLocation id) const;
		std::vector<GridLocation> neighbors(GridLocation id) const;
		double cost(GridLocation from_node, GridLocation to_node) const;
	};
}

/*
namespace std
{
	template <>
	struct hash<pathfinding::SquareGrid::GridLocation>
	{
		std::size_t operator()(const pathfinding::SquareGrid::GridLocation& id) const noexcept
		{
			return std::hash<int>()(id.x ^ (id.y << 16));
		}
	};
}
*/
