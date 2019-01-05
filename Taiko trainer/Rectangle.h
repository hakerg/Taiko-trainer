#pragma once
#include <cmath>
#include "Figure2D.h"
#include "Vector2D.h"

namespace uc
{

	// this is just a rectangle, but this name is already reserved
	// be careful about constructor parameters
	template <class _Numeric> class Rectangle :
		public Figure2D<_Numeric>
	{
	public:

		Vector2D<_Numeric> center, size;

		// center - the center of the rectangle / point where diagonals cross
		// half_size - vector pointed from center to the edge
		Rectangle(const Vector2D<_Numeric> & center_, const Vector2D<_Numeric> & size_) :
			center(center_), size(size_) {}
		virtual ~Rectangle() {}


		Vector2D<double> top_left() const
		{
			return center - size * 0.5;
		}

		Vector2D<double> bottom_right() const
		{
			return center + size * 0.5;
		}

		// excluding border
		bool inside(const Vector2D<_Numeric>& point) const override
		{
			return abs(point.x - center.x) * 2 < size.x && abs(point.y - center.y) * 2 < size.y;
		}
		bool on_border(const Vector2D<_Numeric>& point) const override
		{
			return abs(point.x - center.x) * 2 == size.x && abs(point.y - center.y) * 2 == size.y;
		}

		// including border
		bool over(const Vector2D<_Numeric>& point) const override
		{
			return abs(point.x - center.x) * 2 <= size.x && abs(point.y - center.y) * 2 <= size.y;
		}
		_Numeric area() const override
		{
			return size.x * size.y;
		}
		_Numeric circumference() const override
		{
			return (size.x + size.y) * 2;
		}
	};

}