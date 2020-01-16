#pragma once

#include <memory>

#include "Observer.h"

namespace ABTools
{
	namespace MVC
	{
		class Model : public Observer::Subject
		{
		public:
			using ConstPtr = std::shared_ptr<const Model>;
			using Ptr = std::shared_ptr<Model>;
			using ConstWeakPtr = std::weak_ptr<const Model>;
			using WeakPtr = std::weak_ptr<Model>;

		public:
			virtual ~Model() = default;
		};

		class View : public Observer::Observer
		{
		public:
			using Ptr = std::shared_ptr<View>;
			using WeakPtr = std::weak_ptr<View>;

		public:
			virtual ~View() = default;
		};

		class Controller
		{
		public:
			virtual ~Controller() = default;

		};
	}
}
