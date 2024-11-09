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

	template <typename T, typename priority_t>
	struct PriorityQueue
	{
		typedef std::pair<priority_t, T> PQElement;
		std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

		bool empty() const { return elements.empty(); }
		void put(T item, priority_t priority) { elements.emplace(priority, item); }

		T get()
		{
			T best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};

	inline double heuristic(SquareGrid::Location a, SquareGrid::Location b)
	{
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}

	template <typename Graph>
	void a_star_search(Graph graph,
	                   typename Graph::Location start,
	                   typename Graph::Location target,
	                   std::unordered_map<typename Graph::Location, typename Graph::Location, SquareGrid::LocationHash>& came_from,
	                   std::unordered_map<typename Graph::Location, typename Graph::CostType, SquareGrid::LocationHash>& cost_so_far)
	{
		typedef typename Graph::Location Location;
		typedef typename Graph::CostType CostType;

		PriorityQueue<typename Graph::Location, CostType> frontier;
		std::vector<Location> neighbors;

		frontier.put(start, CostType(0));
		came_from[start] = start;
		cost_so_far[start] = CostType(0);

		while (!frontier.empty())
		{
			Location current = frontier.get();

			if (current == target)
			{
				break;
			}

			for (Location next : graph.neighbors(current))
			{
				CostType new_cost = cost_so_far[current] + graph.cost(current, next);

				if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
				{
					cost_so_far[next] = new_cost;
					CostType priority = new_cost + heuristic(next, target);
					frontier.put(next, priority);
					came_from[next] = current;
				}
			}
		}
	}

	template <typename Location>
	std::vector<Location> reconstruct_path(Location start, Location target,
	                                       std::unordered_map<Location, Location, SquareGrid::LocationHash> came_from)
	{
		std::vector<Location> path;
		Location current = target;

		const bool no_path_found{came_from.find(target) == came_from.end()};

		if (no_path_found)
		{
			return path;
		}

		while (current != start)
		{
			path.push_back(current);
			current = came_from[current];
		}

		path.push_back(start);
		std::reverse(path.begin(), path.end());

		return path;
	}
}
