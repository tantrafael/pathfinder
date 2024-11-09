#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

#include "square_grid.h"

namespace pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath);

	template <typename T, typename TPriority>
	struct PriorityQueue
	{
		typedef std::pair<TPriority, T> Element;

		std::priority_queue<Element, std::vector<Element>, std::greater<>> Elements;

		bool IsEmpty() const
		{
			return Elements.empty();
		}

		void Add(T item, TPriority priority)
		{
			Elements.emplace(priority, item);
		}

		T Get()
		{
			const T TopElement{Elements.top().second};
			Elements.pop();

			return TopElement;
		}
	};

	inline SquareGrid::CostType Heuristic(SquareGrid::Location A, SquareGrid::Location B)
	{
		const int ManhattanDistance{std::abs(A.X - B.X) + std::abs(A.Y - B.Y)};

		return ManhattanDistance;
	}

	template <typename TGraph>
	void AStarSearch(TGraph Graph,
	                 typename TGraph::Location Start,
	                 typename TGraph::Location Goal,
	                 std::unordered_map<typename TGraph::Location, typename TGraph::Location, SquareGrid::LocationHash>& CameFrom,
	                 std::unordered_map<typename TGraph::Location, typename TGraph::CostType, SquareGrid::LocationHash>& CostSoFar)
	{
		typedef typename TGraph::Location Location;
		typedef typename TGraph::CostType CostType;

		PriorityQueue<Location, CostType> Frontier;
		//std::vector<Location> neighbors;

		Frontier.Add(Start, CostType(0));
		CameFrom[Start] = Start;
		CostSoFar[Start] = CostType(0);

		while (!Frontier.IsEmpty())
		{
			const Location Current{Frontier.Get()};

			if (Current == Goal)
			{
				break;
			}

			const std::vector<Location> Neighbors{Graph.GetNeighbors(Current)};
			//graph.get_neighbors(current, neighbors);

			for (const Location Neighbor : Neighbors)
			{
				const CostType Cost{CostSoFar[Current] + Graph.GetCost(Current, Neighbor)};
				const bool IsFirstVisit{CostSoFar.find(Neighbor) == CostSoFar.end()};
				//const bool IsFirstEncounter{!CostSoFar.contains(Neighbor)};
				const bool IsLowerCost{Cost < CostSoFar[Neighbor]};
				const bool IsCostUpdate{IsFirstVisit || IsLowerCost};

				if (IsCostUpdate)
				{
					CostSoFar[Neighbor] = Cost;
					const CostType Priority{Cost + Heuristic(Neighbor, Goal)};
					Frontier.Add(Neighbor, Priority);
					CameFrom[Neighbor] = Current;
				}
			}
		}
	}

	template <typename Location>
	std::vector<Location> ReconstructPath(Location Start, Location Goal,
	                                      std::unordered_map<Location, Location, SquareGrid::LocationHash> CameFrom)
	{
		std::vector<Location> Path;
		Location Current = Goal;

		const bool IsNoPath{CameFrom.find(Goal) == CameFrom.end()};
		//const bool IsNoPath{!CameFrom.contains(Goal)};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			Current = CameFrom[Current];
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}
}
