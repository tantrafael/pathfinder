#pragma once

#include <algorithm>
#include <vector>

namespace pathfinding
{
	template <typename TGraph>
	std::vector<typename TGraph::Location> ReconstructPath(const TGraph& Graph,
	                                                       const typename TGraph::Location Start,
	                                                       const typename TGraph::Location Goal,
	                                                       const std::vector<typename TGraph::Location>& CameFrom)
	{
		const size_t MapLength{static_cast<size_t>(Graph.Width * Graph.Height)};
		const bool IsValidInput{CameFrom.size() == MapLength};
		assert(IsValidInput);

		typedef typename TGraph::Location Location;

		std::vector<Location> Path;
		Location Current = Goal;

		const int GoalIndex{Graph.GetMapIndex(Goal)};
		//const bool IsNoPath{CameFrom[GoalIndex] == SquareGrid::Location::Undefined};
		const bool IsNoPath{CameFrom[GoalIndex] == SquareGrid::Undefined};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			const int CurrentMapIndex{Graph.GetMapIndex(Current)};
			Current = CameFrom[CurrentMapIndex];
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}
}
