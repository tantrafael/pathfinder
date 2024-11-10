#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

#include "square_grid.h"

namespace pathfinding
{
	template <class TGraph>
	void DrawGrid(const TGraph& Graph,
	              std::vector<SquareGrid::CostType>* Costs = nullptr,
	              std::vector<SquareGrid::Location>* CameFrom = nullptr,
	              const std::vector<SquareGrid::Location>* Path = nullptr,
	              SquareGrid::Location* Start = nullptr,
	              SquareGrid::Location* Goal = nullptr)
	{
		const int FieldWidth = 3;
		std::cout << std::string(FieldWidth * Graph.Width, '_') << '\n';

		for (int y = 0; y != Graph.Height; ++y)
		{
			for (int x = 0; x != Graph.Width; ++x)
			{
				SquareGrid::Location id{x, y};

				if (Graph.Impassable.find(id) != Graph.Impassable.end())
				{
					std::cout << std::string(FieldWidth, '#');
				}
				else if (Start && id == *Start)
				{
					std::cout << " A ";
				}
				else if (Goal && id == *Goal)
				{
					std::cout << " Z ";
				}
				else if (Path != nullptr && std::find(Path->begin(), Path->end(), id) != Path->end())
				{
					std::cout << " @ ";
				}
				else if (CameFrom != nullptr && std::find(CameFrom->begin(), CameFrom->end(), id) != CameFrom->end())
				{
					const int LocationIndex{id.Y * Graph.Width + id.X};
					// TODO: Check safety.
					SquareGrid::Location next = (*CameFrom)[LocationIndex];
					if (next.X == x + 1) { std::cout << " > "; }
					else if (next.X == x - 1) { std::cout << " < "; }
					else if (next.Y == y + 1) { std::cout << " v "; }
					else if (next.Y == y - 1) { std::cout << " ^ "; }
					else { std::cout << " * "; }
				}
				else if (Costs != nullptr)
				{
					const int LocationIndex{id.Y * Graph.Width + id.X};
					// TODO: Check safety.
					std::cout << ' ' << std::left << std::setw(FieldWidth - 1) << (*Costs)[LocationIndex];
				}
				else
				{
					std::cout << " . ";
				}
			}

			std::cout << '\n';
		}

		std::cout << std::string(FieldWidth * Graph.Width, '~') << '\n';
	}
}
