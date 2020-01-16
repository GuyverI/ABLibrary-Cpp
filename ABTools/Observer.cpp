#include "Observer.h"

#include <algorithm>

namespace ABTools
{
	namespace Observer
	{
		void Subject::Subscribe(const Observer::Ptr observer)
		{
			if (observer && Find(*observer) == _subscribers.cend())
			{
				_subscribers.emplace_back(observer);
			}
		}

		void Subject::Unsubscribe(const Observer& observer)
		{
			const auto it = Find(observer);
			if (it != _subscribers.cend())
			{
				_subscribers.erase(it);
			}
		}

		void Subject::Notify()
		{
			for (auto it = _subscribers.begin(); it != _subscribers.end();)
			{
				const auto subscriber = it->lock();
				if (subscriber)
				{
					subscriber->OnNotified();
					++it;
				}
				else
				{
					it = _subscribers.erase(it);
				}
			}
		}

		std::vector<Observer::WeakPtr>::const_iterator Subject::Find(const Observer& observer) const
		{
			return std::find_if(_subscribers.cbegin(), _subscribers.cend(), [&observer](const auto& subscriber) -> bool
			{
				return &observer == subscriber.lock().get();
			});
		}
	}
}


