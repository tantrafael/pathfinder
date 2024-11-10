#pragma once

//#include <unordered_map>
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
					 //std::unordered_map<typename TGraph::Location, typename TGraph::Location, SquareGrid::LocationHash>& OutCameFrom,
					 std::vector<SquareGrid::Location>& OutCameFrom,
					 //std::unordered_map<typename TGraph::Location, typename TGraph::CostType, SquareGrid::LocationHash>& OutCostSoFar)
					 std::vector<typename TGraph::CostType>& OutCostSoFar)
	{
		typedef typename TGraph::Location Location;
		typedef typename TGraph::CostType CostType;

		PriorityQueue<Location, CostType> Frontier{};
		std::vector<Location> Neighbors{};

		Frontier.Add(Start, CostType(0));

		//OutCameFrom[Start] = Start;
		const int StartIndex{Start.Y * Graph.Width + Start.X};
		OutCameFrom[StartIndex] = Start;
		//OutCostSoFar[Start] = CostType(0);
		OutCostSoFar[StartIndex] = CostType(0);

		while (!Frontier.IsEmpty())
		{
			const Location Current{Frontier.Get()};

			if (Current == Goal)
			{
				break;
			}

			//const std::vector<Location> Neighbors{Graph.GetNeighbors(Current)};
			Graph.GetNeighbors(Current, Neighbors);

			for (const Location Neighbor : Neighbors)
			{
				//const CostType Cost{OutCostSoFar[Current] + Graph.GetCost(Current, Neighbor)};
				const int CurrentIndex{Current.Y * Graph.Width + Current.X};
				const CostType Cost{OutCostSoFar[CurrentIndex] + Graph.GetCost(Current, Neighbor)};
				//const bool IsFirstVisit{OutCostSoFar.find(Neighbor) == OutCostSoFar.end()};
				const int NeighborIndex{Neighbor.Y * Graph.Width + Neighbor.X};
				const bool IsFirstVisit{OutCostSoFar[NeighborIndex] == 0};
				//const bool IsFirstEncounter{!CostSoFar.contains(Neighbor)};
				//const bool IsLowerCost{Cost < OutCostSoFar[Neighbor]};
				const bool IsLowerCost{Cost < OutCostSoFar[NeighborIndex]};
				const bool IsCostUpdate{IsFirstVisit || IsLowerCost};

				if (IsCostUpdate)
				{
					//OutCostSoFar[Neighbor] = Cost;
					OutCostSoFar[NeighborIndex] = Cost;
					const CostType Priority{Cost + Heuristic(Neighbor, Goal)};
					Frontier.Add(Neighbor, Priority);
					//OutCameFrom[Neighbor] = Current;
					//const int NeighborIndex{Neighbor.Y * Graph.Width + Neighbor.X};
					OutCameFrom[NeighborIndex] = Current;
				}
			}
		}
	}

	template <typename TLocation>
	std::vector<TLocation> ReconstructPath(TLocation Start,
	                                       TLocation Goal,
	                                       //const std::unordered_map<TLocation, TLocation, SquareGrid::LocationHash>& CameFrom)
	                                       const std::vector<TLocation>& CameFrom,
	                                       std::pair<int, int> MapDimensions)
	{
		std::vector<TLocation> Path;
		TLocation Current = Goal;

		//const bool IsNoPath{CameFrom.find(Goal) == CameFrom.end()};
		const bool IsNoPath{std::find(CameFrom.begin(), CameFrom.end(), Current) != CameFrom.end()};
		//const bool IsNoPath{!CameFrom.contains(Goal)};

		if (IsNoPath)
		{
			return Path;
		}

		while (Current != Start)
		{
			Path.push_back(Current);
			//Current = CameFrom.at(Current);
			const int CurrentIndex{Current.Y * MapDimensions.first + Current.X};
			Current = CameFrom.at(CurrentIndex);
		}

		Path.push_back(Start);
		std::reverse(Path.begin(), Path.end());

		return Path;
	}
}
