#include "graph.h"
#include <tuple>

std::vector<char> SimpleGraph::neighbors(char id)
{
	return edges[id];
}

bool operator ==(GridLocation a, GridLocation b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator !=(GridLocation a, GridLocation b)
{
	return !(a == b);
}

bool operator <(GridLocation a, GridLocation b)
{
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

namespace std
{
	std::size_t hash<GridLocation>::operator()(const GridLocation& id) const noexcept
	{
		return std::hash<int>()(id.x ^ (id.y << 16));
	}
}
