#pragma once

#include <queue>

namespace pathfinding
{
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
}