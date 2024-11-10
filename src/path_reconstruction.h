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
		// TODO: Assert correct dimensions of CameFrom.

		typedef typename TGraph::Location Location;

		std::vector<Location> Path;
		Location Current = Goal;

		const bool IsNoPath{std::find(CameFrom.begin(), CameFrom.end(), Current) == CameFrom.end()};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			const int CurrentMapIndex{Graph.GetMapIndex(Current)};
			// TODO: Check safety.
			Current = CameFrom[CurrentMapIndex];
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}
}
