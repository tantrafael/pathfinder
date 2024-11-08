#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

struct SimpleGraph
{
	std::unordered_map<char, std::vector<char>> edges;
	std::vector<char> neighbors(char id);
};

struct GridLocation
{
	int x, y;
};

bool operator ==(GridLocation a, GridLocation b);
bool operator !=(GridLocation a, GridLocation b);
bool operator <(GridLocation a, GridLocation b);

namespace std
{
	template <>
	struct hash<GridLocation>
	{
		std::size_t operator()(const GridLocation& id) const noexcept;
	};
}
