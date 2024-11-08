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

		inline bool empty() const { return elements.empty(); }
		inline void put(T item, priority_t priority) { elements.emplace(priority, item); }

		T get()
		{
			T best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};

	inline double heuristic(GridLocation a, GridLocation b)
	{
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}

	template <typename Location, typename Graph>
	void a_star_search(Graph graph, Location start, Location goal,
	                   std::unordered_map<Location, Location>& came_from,
	                   std::unordered_map<Location, double>& cost_so_far)
	{
		PriorityQueue<Location, double> frontier;
		frontier.put(start, 0);
		came_from[start] = start;
		cost_so_far[start] = 0;

		while (!frontier.empty())
		{
			Location current = frontier.get();

			if (current == goal) break;

			for (Location next : graph.neighbors(current))
			{
				double new_cost = cost_so_far[current] + graph.cost(current, next);

				if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
				{
					cost_so_far[next] = new_cost;
					double priority = new_cost + heuristic(next, goal);
					frontier.put(next, priority);
					came_from[next] = current;
				}
			}
		}
	}

	template <typename Location>
	std::vector<Location> reconstruct_path(Location start, Location goal,
	                                       std::unordered_map<Location, Location> came_from)
	{
		std::vector<Location> path;
		Location current = goal;

		// No path found.
		if (came_from.find(goal) == came_from.end())
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
