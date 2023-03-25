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

		template<class T>
		class View : public Observer::Observer
		{
		public:
			using Ptr = std::shared_ptr<View>;
			using WeakPtr = std::weak_ptr<View>;

		public:
			explicit View(const std::shared_ptr<T>& model);
			virtual ~View() = default;

			T* GetModel();
			void SetModel(const std::shared_ptr<T>& model);

		private:
			std::shared_ptr<T> _model;
		};

		class Controller
		{
		public:
			virtual ~Controller() = default;

		};

		template<class T>
		View<T>::View(const std::shared_ptr<T>& model)
			: _model(model)
		{}

		template<class T>
		T* View<T>::GetModel()
		{
			return _model.get();
		}

		template<class T>
		void View<T>::SetModel(const std::shared_ptr<T>& model)
		{
			_model = model;
		}

		template<class T>
		void AttachModelAndNotify(const typename View<T>::Ptr& view, const std::shared_ptr<T>& model)
		{
			if (!view)
				return;

			if (model)
				model->Subscribe(view);

			view->SetModel(model);
			view->OnNotified();
		}

		template<class T>
		void ReplaceModelAndNotify(const typename View<T>::Ptr& view, const std::shared_ptr<T>& model)
		{
			if (!view)
				return;

			if (const auto prevModel = view->GetModel())
				prevModel->Unsubscribe(*view);

			if (model)
				model->Subscribe(view);

			view->SetModel(model);
			view->OnNotified();
		}
	}
}
