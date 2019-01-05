#pragma once
#include "Vector2D.h"

namespace uc
{

	template <class _Numeric> class Figure2D
	{
	public:
		Figure2D() {}
		virtual ~Figure2D() {}

		// excluding border
		virtual bool inside(const Vector2D<_Numeric> & point) const = 0;

		virtual bool on_border(const Vector2D<_Numeric> & point) const = 0;

		// including border
		virtual bool over(const Vector2D<_Numeric> & point) const = 0;

		virtual _Numeric area() const = 0;
		virtual _Numeric circumference() const = 0;
	};

}