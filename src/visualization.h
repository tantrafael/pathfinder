#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

#include "square_grid.h"

namespace pathfinding
{
	// This function outputs a grid. Pass in optional parameters to print
	// the distances, point_to directions, or a path.
	template <class Graph>
	void DrawGrid(const Graph& graph,
	              //std::unordered_map<SquareGrid::Location, SquareGrid::CostType, SquareGrid::LocationHash>* distances = nullptr,
	              std::vector<SquareGrid::CostType>* distances = nullptr,
	              //std::unordered_map<SquareGrid::Location, SquareGrid::Location, SquareGrid::LocationHash>* point_to = nullptr,
	              std::vector<SquareGrid::Location>* point_to = nullptr,
	              const std::vector<SquareGrid::Location>* path = nullptr,
	              SquareGrid::Location* start = nullptr,
	              SquareGrid::Location* target = nullptr)
	{
		const int field_width = 3;
		std::cout << std::string(field_width * graph.Width, '_') << '\n';

		for (int y = 0; y != graph.Height; ++y)
		{
			for (int x = 0; x != graph.Width; ++x)
			{
				SquareGrid::Location id{x, y};

				if (graph.Impassable.find(id) != graph.Impassable.end())
				{
					std::cout << std::string(field_width, '#');
				}
				else if (start && id == *start)
				{
					std::cout << " A ";
				}
				else if (target && id == *target)
				{
					std::cout << " Z ";
				}
				else if (path != nullptr && std::find(path->begin(), path->end(), id) != path->end())
				{
					std::cout << " @ ";
				}
				//else if (point_to != nullptr && point_to->count(id))
				else if (point_to != nullptr && std::find(point_to->begin(), point_to->end(), id) != point_to->end())
				{
					//SquareGrid::Location next = (*point_to)[id];
					const int LocationIndex{id.Y * graph.Width + id.X};
					SquareGrid::Location next = (*point_to)[LocationIndex];
					if (next.X == x + 1) { std::cout << " > "; }
					else if (next.X == x - 1) { std::cout << " < "; }
					else if (next.Y == y + 1) { std::cout << " v "; }
					else if (next.Y == y - 1) { std::cout << " ^ "; }
					else { std::cout << " * "; }
				}
				//else if (distances != nullptr && distances->count(id))
				else if (distances != nullptr)
				{
					//std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
					const int LocationIndex{id.Y * graph.Width + id.X};
					std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[LocationIndex];
				}
				else
				{
					std::cout << " . ";
				}
			}

			std::cout << '\n';
		}

		std::cout << std::string(field_width * graph.Width, '~') << '\n';
	}
}
