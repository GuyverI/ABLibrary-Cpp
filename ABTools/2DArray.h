#pragma once
#include <functional>
#include <vector>

namespace AB
{
	//TODO: AB - implement empty state
	template<class T>
	class TwoDArray final
	{
	public:
		class Iterator
		{
		public:
			Iterator() = delete;

			bool operator==(const Iterator& other) const
			{
				return _container == other._container
					&& _row == other._row
					&& _col == other._col;
			}

			bool operator!=(const Iterator& other) const
			{
				return !operator==(other);
			}

			Iterator& operator++()
			{
				if (_container && !_container->IsZeroSize())
				{
					if (_col < _container->GetColCount() - 1)
					{
						++_col;
					}
					else if (_row < _container->GetRowCount() - 1)
					{
						NextRow()
					}
					else if (IsLastPosition())
					{
						NextRow();
					}
				}

				return *this;
			}

			const T& operator*() const
			{
				return _container->At(_row, _col);
			}

			T& operator*()
			{
				return _container->At(_row, _col);
			}

		private:
			friend TwoDArray<T>;

		private:
			Iterator(TwoDArray<T>* container, const size_t row, const size_t col)
				: _container(container)
				, _row(row)
				, _col(col)
			{}

			bool IsLastPosition() const
			{
				return _row == _container->GetRowCount() - 1 && _col == _container->GetColCount() - 1;
			}

			void NextRow()
			{
				++_row;
				_col = 0;
			}

		private:
			TwoDArray<T>* _container;
			size_t _row;
			size_t _col;
		};

	public:
		TwoDArray()
			: TwoDArray(0, 0, T())
		{}

		TwoDArray(const size_t rowCount, const size_t colCount, const T& defVal)
			: _data()
		{
			if (rowCount > 0 && colCount > 0)
			{
				_data.assign(rowCount, std::vector<T>(colCount, defVal)
			}
		}

		size_t GetRowCount() const
		{
			return _data.size();
		}

		size_t GetColCount() const
		{
			if (!_data.empty())
			{
				return _data.front().size();
			}

			return 0;
		}

		bool IsZeroSize() const
		{
			return GetColCount() == 0 || GetRowCount() == 0;
		}

		const T& At(const size_t row, const size_t col) const
		{
			return _data[row][col];
		}

		T& At(const size_t row, const size_t col)
		{
			return const_cast<T&>(static_cast<const TwoDArray&>(*this).At(row, col));
		}

		void ForEach(const std::function<void(T&)>& func)
		{
			for (auto& row : _data)
			{
				for (auto& item : row)
				{
					func(item);
				}
			}
		}

		void ForEach(const std::function<void(const T&)>& func) const
		{
			for (auto& row : _data)
			{
				for (auto& item : row)
				{
					func(item);
				}
			}
		}

		Iterator GetBeginIterator()
		{
			return Iterator(this, 0, 0);
		}

		Iterator GetEndIterator()
		{
			return Iterator(this, GetRowCount(), 0);
		}

	private:
		std::vector<std::vector<T>> _data;
	};
}

template<class T>
typename AB::TwoDArray<T>::Iterator begin(AB::TwoDArray<T>& container)
{
	return container.GetBeginIterator();
}

template<class T>
typename AB::TwoDArray<T>::Iterator end(AB::TwoDArray<T>& container)
{
	return container.GetEndIterator();
}