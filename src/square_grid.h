#pragma once

#include <array>
#include <unordered_set>
#include <vector>

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

namespace pathfinding
{
	bool operator ==(GridLocation a, GridLocation b);
	bool operator !=(GridLocation a, GridLocation b);
	bool operator <(GridLocation a, GridLocation b);

	struct SquareGrid
	{
		static std::array<GridLocation, 4> DIRS;
		int width, height;
		std::unordered_set<GridLocation> walls;

		SquareGrid(int width_, int height_);
		bool in_bounds(GridLocation id) const;
		bool passable(GridLocation id) const;
		std::vector<GridLocation> neighbors(GridLocation id) const;
		double cost(GridLocation from_node, GridLocation to_node) const;
	};
}
