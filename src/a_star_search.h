#pragma once

#include <cassert>
#include <functional>
#include <cmath>
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

	/*
	template <typename TGraph>
	void AStarSearch(const TGraph& Graph,
	                 const typename TGraph::Location Start,
	                 const typename TGraph::Location Goal,
	                 std::function<typename TGraph::CostType(typename TGraph::Location Location,
	                                                         typename TGraph::Location Goal)> Heuristic,
	                 std::vector<SquareGrid::Location>& OutCameFrom,
	                 std::vector<typename TGraph::CostType>& OutCostSoFar)
	{
		const size_t MapLength{static_cast<size_t>(Graph.Width * Graph.Height)};
		const bool IsValidInput{(OutCameFrom.size() == MapLength) && (OutCostSoFar.size() == MapLength)};
		assert(IsValidInput);

		typedef typename TGraph::Location Location;
		typedef typename TGraph::CostType CostType;

		PriorityQueue<Location, CostType> Frontier{};
		std::vector<Location> Neighbors{};

		Frontier.Add(Start, CostType(0));

		const int StartMapIndex{Graph.GetMapIndex(Start)};
		OutCameFrom[StartMapIndex] = Start;
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
				//const CostType Cost{OutCostSoFar[CurrentMapIndex] + Graph.GetCost(Current, Neighbor)};
				const CostType Cost{OutCostSoFar[CurrentMapIndex] + Graph.Cost};
				const bool IsFirstVisit{OutCostSoFar[NeighborMapIndex] == 0};
				const bool IsLowerCost{Cost < OutCostSoFar[NeighborMapIndex]};
				const bool IsCostUpdate{IsFirstVisit || IsLowerCost};

				if (IsCostUpdate)
				{
					OutCostSoFar[NeighborMapIndex] = Cost;
					const CostType Priority{Cost + Heuristic(Neighbor, Goal)};
					Frontier.Add(Neighbor, Priority);
					OutCameFrom[NeighborMapIndex] = Current;
				}
			}
		}
	}
	*/
	struct AStarSearchOutput
	{
		std::vector<SquareGrid::Location> CameFrom;
		std::vector<SquareGrid::CostType> CostSoFar;
	};

	template <typename TGraph>
	AStarSearchOutput AStarSearch(const TGraph& Graph,
	                              const typename TGraph::Location Start,
	                              const typename TGraph::Location Goal,
	                              std::function<typename TGraph::CostType(typename TGraph::Location Location,
	                                                                      typename TGraph::Location Goal)> Heuristic)
	{
		const int MapLength{Graph.Width * Graph.Height};
		std::vector<SquareGrid::Location> CameFrom(MapLength, SquareGrid::Undefined);
		std::vector<SquareGrid::CostType> CostSoFar(MapLength, 0);

		typedef typename TGraph::Location Location;
		typedef typename TGraph::CostType CostType;

		PriorityQueue<Location, CostType> Frontier{};
		//std::vector<Location> Neighbors{};

		Frontier.Add(Start, CostType(0));

		const int StartMapIndex{Graph.GetMapIndex(Start)};
		CameFrom[StartMapIndex] = Start;
		CostSoFar[StartMapIndex] = CostType(0);

		while (!Frontier.IsEmpty())
		{
			const Location Current{Frontier.Get()};

			if (Current == Goal)
			{
				break;
			}

			//Graph.GetNeighbors(Current, Neighbors);
			const std::vector<Location> Neighbors{Graph.GetNeighbors(Current)};

			for (const Location Neighbor : Neighbors)
			{
				const int CurrentMapIndex{Graph.GetMapIndex(Current)};
				const int NeighborMapIndex{Graph.GetMapIndex(Neighbor)};
				//const CostType Cost{OutCostSoFar[CurrentMapIndex] + Graph.GetCost(Current, Neighbor)};
				const CostType Cost{CostSoFar[CurrentMapIndex] + Graph.Cost};
				const bool IsFirstVisit{CostSoFar[NeighborMapIndex] == 0};
				const bool IsLowerCost{Cost < CostSoFar[NeighborMapIndex]};
				const bool IsCostUpdate{IsFirstVisit || IsLowerCost};

				if (IsCostUpdate)
				{
					CostSoFar[NeighborMapIndex] = Cost;
					const CostType Priority{Cost + Heuristic(Neighbor, Goal)};
					Frontier.Add(Neighbor, Priority);
					CameFrom[NeighborMapIndex] = Current;
				}
			}
		}

		return AStarSearchOutput{CameFrom, CostSoFar};
	}
}
