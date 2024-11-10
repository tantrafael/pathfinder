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
			int X, Y;

			bool operator ==(Location Other) const;
			bool operator !=(Location Other) const;
			bool operator <(Location Other) const;
		};

		struct LocationHash
		{
			std::size_t operator()(Location GridLocation) const noexcept;
		};

		typedef int CostType;

		static std::array<Location, 4> Directions;
		int Width, Height;
		std::unordered_set<Location, LocationHash> Impassable;

		SquareGrid(int Width, int Height);
		bool IsWithinBounds(Location GridLocation) const;
		bool IsPassable(Location GridLocation) const;
		void GetNeighbors(Location GridLocation, std::vector<Location>& OutNeighbors) const;
		static CostType GetCost(Location FromLocation, Location ToLocation);
		int GetMapIndex(Location GridLocation) const;
	};
}
