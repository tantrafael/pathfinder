#pragma once

#include <iostream>
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
	              const SquareGrid::Location* Start = nullptr,
	              const SquareGrid::Location* Goal = nullptr)
	{
		const size_t MapLength{static_cast<size_t>(Graph.Width * Graph.Height)};

		const int FieldWidth{3};

		std::cout << std::string(FieldWidth * Graph.Width, '_') << '\n';

		for (int Row{0}; Row != Graph.Height; Row++)
		{
			for (int Column{0}; Column != Graph.Width; Column++)
			{
				SquareGrid::Location GridLocation{Column, Row};

				if (Graph.Impassable.find(GridLocation) != Graph.Impassable.end())
				{
					std::cout << std::string(FieldWidth, '#');
				}
				else if (Start && GridLocation == *Start)
				{
					std::cout << " A ";
				}
				else if (Goal && GridLocation == *Goal)
				{
					std::cout << " Z ";
				}
				else if (Path != nullptr && std::find(Path->begin(), Path->end(), GridLocation) != Path->end())
				{
					std::cout << " @ ";
				}
				else if (CameFrom != nullptr && std::find(CameFrom->begin(), CameFrom->end(), GridLocation) != CameFrom->end())
				{
					const bool IsMatchingDimensions{CameFrom->size() == MapLength};
					assert(IsMatchingDimensions);

					const int LocationIndex{Graph.GetMapIndex(GridLocation)};
					SquareGrid::Location Next = (*CameFrom)[LocationIndex];
					if (Next.X == Column + 1) { std::cout << " > "; }
					else if (Next.X == Column - 1) { std::cout << " < "; }
					else if (Next.Y == Row + 1) { std::cout << " v "; }
					else if (Next.Y == Row - 1) { std::cout << " ^ "; }
					else { std::cout << " * "; }
				}
				else if (Costs != nullptr)
				{
					const bool IsMatchingDimensions{Costs->size() == MapLength};
					assert(IsMatchingDimensions);

					const int LocationIndex{GridLocation.Y * Graph.Width + GridLocation.X};
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
