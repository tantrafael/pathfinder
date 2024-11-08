#include <unordered_map>
#include <vector>

#include "pathfinding.h"
#include "grid_initialization.h"
#include "visualization.h"

int main() {
	pathfinding::SquareGrid grid = pathfinding::make_diagram1();

	std::unordered_map<pathfinding::GridLocation, pathfinding::GridLocation> came_from;
	std::unordered_map<pathfinding::GridLocation, double> cost_so_far;

	pathfinding::GridLocation start{8, 7};
	pathfinding::GridLocation goal{23, 4};

	pathfinding::a_star_search(grid, start, goal, came_from, cost_so_far);

	pathfinding::draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
	std::cout << '\n';

	std::vector<pathfinding::GridLocation> path = pathfinding::reconstruct_path(start, goal, came_from);
	pathfinding::draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
	std::cout << '\n';

	pathfinding::draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}
