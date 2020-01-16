#pragma once

#include <memory>
#include <vector>

namespace ABTools
{
	namespace Observer
	{
		class Observer
		{
		public:
			using Ptr = std::shared_ptr<Observer>;
			using WeakPtr = std::weak_ptr<Observer>;

		public:
			virtual ~Observer() = default;

			virtual void OnNotified() = 0;
		};

		class Subject
		{
		public:
			virtual ~Subject() = default;

			void Subscribe(const Observer::Ptr observer);
			void Unsubscribe(const Observer& observer);

		protected:
			void Notify();

		private:
			std::vector<Observer::WeakPtr>::const_iterator Find(const Observer& observer) const;

		private:
			std::vector<Observer::WeakPtr> _subscribers;
		};
	}
}
