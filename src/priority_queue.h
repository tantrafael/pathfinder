#pragma once

#include <queue>
#include <mutex>

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

		void Add(TLocation Item, TPriority Priority)
		{
			std::lock_guard<std::mutex> lock(QueueMutex);
			Elements.emplace(Priority, Item);
		}

		TLocation Get()
		{
			std::lock_guard<std::mutex> lock(QueueMutex);
			const TLocation TopElement{Elements.top().second};
			Elements.pop();

			return TopElement;
		}

	private:
		mutable std::mutex QueueMutex;
	};
}
