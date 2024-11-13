#pragma once

#include <array>
//#include <mutex>
#include <unordered_set>
#include <vector>

namespace pathfinding
{
	struct SquareGrid
	{
		struct Location
		{
			int X, Y;

			//static constexpr Location Undefined{-1, -1};

			bool operator ==(Location Other) const;
			bool operator !=(Location Other) const;
			bool operator <(Location Other) const;
		};

		static constexpr Location Undefined{-1, -1};

		struct LocationHash
		{
			std::size_t operator()(Location GridLocation) const noexcept;
		};

		typedef int CostType;

		//static std::array<Location, 4> Directions;
		static constexpr std::array<Location, 4> Directions{
			Location{1, 0}, Location{-1, 0}, Location{0, -1}, Location{0, 1}
		};
		int Width, Height;
		std::unordered_set<Location, LocationHash> Impassable;

		SquareGrid(int Width, int Height);
		bool CheckWithinBounds(Location GridLocation) const;
		bool CheckPassable(Location GridLocation) const;
		//void GetNeighbors(Location GridLocation, std::vector<Location>& OutNeighbors) const;
		std::vector<Location> GetNeighbors(Location GridLocation) const;
		//static CostType GetCost(Location FromLocation, Location ToLocation);
		static constexpr CostType Cost{1};
		int GetMapIndex(Location GridLocation) const;

	/*
	private:
		mutable std::mutex ImpassableMutex;
		friend SquareGrid ParseMap(const std::vector<int>& Map, std::pair<int, int> MapDimensions);
	*/
	};
}
