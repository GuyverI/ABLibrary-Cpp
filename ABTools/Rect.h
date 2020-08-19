#pragma once
#include "../2DVector/2DVector.h"

namespace AB
{
	template<class T>
	class Rect
	{
	public:
		using Position = TwoDVector<T>;

	public:
		Rect()
			: Rect(T(), T(), T(), T())
		{}

		Rect(const T& left, const T& upper, const T& right, const T& bottom)
			: _left(left)
			, _upper(upper)
			, _right(right)
			, _bottom(bottom)
		{}

		Rect(const Position& pos, const T& width, const T& height)
			: Rect(pos.x, pos.y, pos.x + width, pos.y + height)
		{}


		T GetWidth() const
		{
			return std::abs(_right - _left);
		}

		T GetHeight() const
		{
			return std::abs(_upper - _bottom);
		}

		void SetSize(const T& width, const T& height)
		{
			_right = _left + width;
			_bottom = _upper + height;
		}


		Position GetPosition() const
		{
			return Position(_left, _upper);
		}

		void SetPosition(const T& x, const T& y)
		{
			const auto width = GetWidth();
			const auto height = GetHeight();

			_left = x;
			_upper = y;
			SetSize(width, height);
		}		


		Position GetCenter() const
		{
			const auto xCenter = static_cast<T>(_left + GetWidth() / 2);
			const auto yCenter = static_cast<T>(_upper + GetHeight() / 2);

			return Position(xCenter, yCenter);
		}


		bool IsPointInside(const T& x, const T& y) const
		{
			if (x < _left || x > _right)
				return false;

			if (y < _upper || y > _bottom)
				return false;

			return true;
		}

	private:
		T _left, _upper, _right, _bottom;
	};
}