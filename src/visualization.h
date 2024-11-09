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
	/*
	void draw_grid(const Graph& graph,
				   std::unordered_map<GridLocation, double>* distances = nullptr,
				   std::unordered_map<GridLocation, GridLocation>* point_to = nullptr,
				   std::vector<GridLocation>* path = nullptr,
				   GridLocation* start = nullptr,
				   GridLocation* target = nullptr)
	*/
	/*
	void draw_grid(const Graph& graph,
				   std::unordered_map<SquareGrid::GridLocation, double>* distances = nullptr,
				   std::unordered_map<SquareGrid::GridLocation, SquareGrid::GridLocation>* point_to = nullptr,
				   std::vector<SquareGrid::GridLocation>* path = nullptr,
				   SquareGrid::GridLocation* start = nullptr,
				   SquareGrid::GridLocation* target = nullptr)
	*/
	void draw_grid(const Graph& graph,
				   std::unordered_map<SquareGrid::GridLocation, double, SquareGrid::GridLocation_hash>* distances = nullptr,
				   std::unordered_map<SquareGrid::GridLocation, SquareGrid::GridLocation, SquareGrid::GridLocation_hash>* point_to = nullptr,
				   std::vector<SquareGrid::GridLocation>* path = nullptr,
				   SquareGrid::GridLocation* start = nullptr,
				   SquareGrid::GridLocation* target = nullptr)
	{
		const int field_width = 3;
		std::cout << std::string(field_width * graph.width, '_') << '\n';

		for (int y = 0; y != graph.height; ++y)
		{
			for (int x = 0; x != graph.width; ++x)
			{
				//GridLocation id{x, y};
				SquareGrid::GridLocation id{x, y};

				if (graph.impassable.find(id) != graph.impassable.end())
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
				else if (point_to != nullptr && point_to->count(id))
				{
					//GridLocation next = (*point_to)[id];
					SquareGrid::GridLocation next = (*point_to)[id];
					if (next.x == x + 1) { std::cout << " > "; }
					else if (next.x == x - 1) { std::cout << " < "; }
					else if (next.y == y + 1) { std::cout << " v "; }
					else if (next.y == y - 1) { std::cout << " ^ "; }
					else { std::cout << " * "; }
				}
				else if (distances != nullptr && distances->count(id))
				{
					std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
				}
				else
				{
					std::cout << " . ";
				}
			}

			std::cout << '\n';
		}

		std::cout << std::string(field_width * graph.width, '~') << '\n';
	}
}
