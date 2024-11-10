#pragma once

#include <functional>
#include <vector>

#include "priority_queue.h"
#include "square_grid.h"

namespace pathfinding
{
	inline SquareGrid::CostType Heuristic(SquareGrid::Location Location, SquareGrid::Location Goal)
	{
		const int ManhattanDistance{std::abs(Goal.X - Location.X) + std::abs(Goal.Y - Location.Y)};

		return ManhattanDistance;
	}

	template <typename TGraph>
	void AStarSearch(const TGraph& Graph,
	                 const typename TGraph::Location Start,
	                 const typename TGraph::Location Goal,
	                 std::function<typename TGraph::CostType(typename TGraph::Location Location,
	                                                         typename TGraph::Location Goal)> Heuristic,
	                 std::vector<SquareGrid::Location>& OutCameFrom,
	                 std::vector<typename TGraph::CostType>& OutCostSoFar)
	{
		// TODO: Assert correct dimensions of OutCameFrom and OutCostSoFar.

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
}
