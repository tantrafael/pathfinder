#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <functional>

#include "square_grid.h"

namespace pathfinding
{
	bool FindPath(std::pair<int, int> Start,
	              std::pair<int, int> Target,
	              const std::vector<int>& Map,
	              std::pair<int, int> MapDimensions,
	              std::vector<int>& OutPath);

	// TODO: Put PriorityQueue in a separate file.
	template <typename TLocation, typename TPriority>
	struct PriorityQueue
	{
		typedef std::pair<TPriority, TLocation> Element;

		std::priority_queue<Element, std::vector<Element>, std::greater<>> Elements;

		bool IsEmpty() const
		{
			return Elements.empty();
		}

		void Add(TLocation item, TPriority priority)
		{
			Elements.emplace(priority, item);
		}

		TLocation Get()
		{
			const TLocation TopElement{Elements.top().second};
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
	void AStarSearch(const TGraph& Graph,
					 const typename TGraph::Location Start,
					 const typename TGraph::Location Goal,
					 std::function<typename TGraph::CostType(typename TGraph::Location A, typename TGraph::Location B)> Heuristic,
					 std::vector<SquareGrid::Location>& OutCameFrom,
					 std::vector<typename TGraph::CostType>& OutCostSoFar)
	{
		typedef typename TGraph::Location Location;
		typedef typename TGraph::CostType CostType;

		PriorityQueue<Location, CostType> Frontier{};
		std::vector<Location> Neighbors{};

		Frontier.Add(Start, CostType(0));

		const int StartMapIndex{Graph.GetMapIndex(Start)};
		// TODO: Check safety.
		OutCameFrom[StartMapIndex] = Start;
		// TODO: Check safety.
		OutCostSoFar[StartMapIndex] = CostType(0);

		while (!Frontier.IsEmpty())
		{
			const Location Current{Frontier.Get()};

			if (Current == Goal)
			{
				break;
			}

			Graph.GetNeighbors(Current, Neighbors);

			for (const Location Neighbor : Neighbors)
			{
				const int CurrentMapIndex{Graph.GetMapIndex(Current)};
				const int NeighborMapIndex{Graph.GetMapIndex(Neighbor)};
				// TODO: Check safety.
				const CostType Cost{OutCostSoFar[CurrentMapIndex] + Graph.GetCost(Current, Neighbor)};
				// TODO: Check safety.
				const bool IsFirstVisit{OutCostSoFar[NeighborMapIndex] == 0};
				// TODO: Check safety.
				const bool IsLowerCost{Cost < OutCostSoFar[NeighborMapIndex]};
				const bool IsCostUpdate{IsFirstVisit || IsLowerCost};

				if (IsCostUpdate)
				{
					// TODO: Check safety.
					OutCostSoFar[NeighborMapIndex] = Cost;
					const CostType Priority{Cost + Heuristic(Neighbor, Goal)};
					Frontier.Add(Neighbor, Priority);
					// TODO: Check safety.
					OutCameFrom[NeighborMapIndex] = Current;
				}
			}
		}
	}

	// TODO: Handle index calculation differently.
	/*
	template <typename TLocation>
	std::vector<TLocation> ReconstructPath(TLocation Start,
	                                       TLocation Goal,
	                                       const std::vector<TLocation>& CameFrom,
	                                       std::pair<int, int> MapDimensions)
	{
		std::vector<TLocation> Path;
		TLocation Current = Goal;

		const bool IsNoPath{std::find(CameFrom.begin(), CameFrom.end(), Current) != CameFrom.end()};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			const int CurrentIndex{Current.Y * MapDimensions.first + Current.X};
			// TODO: Check safety.
			Current = CameFrom[CurrentIndex];
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}
	*/

	template <typename TGraph>
	std::vector<typename TGraph::Location> ReconstructPath(const TGraph& Graph,
	                                                       const typename TGraph::Location Start,
	                                                       const typename TGraph::Location Goal,
	                                                       const std::vector<typename TGraph::Location>& CameFrom)
	{
		typedef typename TGraph::Location Location;

		std::vector<Location> Path;
		Location Current = Goal;

		const bool IsNoPath{std::find(CameFrom.begin(), CameFrom.end(), Current) != CameFrom.end()};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			//const int CurrentIndex{Current.Y * MapDimensions.first + Current.X};
			const int CurrentMapIndex{Graph.GetMapIndex(Current)};
			// TODO: Check safety.
			Current = CameFrom[CurrentMapIndex];
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}

}
