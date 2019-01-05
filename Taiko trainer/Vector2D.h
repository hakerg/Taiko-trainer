#pragma once
#include <cmath>
#include <type_traits>

namespace uc
{

	// geometric 2D vector
	template <class _Numeric> class Vector2D
	{
	public:

		_Numeric x, y;


		Vector2D(_Numeric x_, _Numeric y_) : x(x_), y(y_) {}

		template <class _Numeric1, class _Numeric2>
		Vector2D(const Vector2D<_Numeric1> & _from, const Vector2D<_Numeric2> & _to) : x(_to.x - _from.x), y(_to.y - _from.y) {}

		virtual ~Vector2D() {}

		static Vector2D<_Numeric> FromPolar(double length, double rotation)
		{
			return { length * cos(rotation), length * sin(rotation) };
		}

		static Vector2D<_Numeric> zeros()
		{
			return { 0, 0 };
		}

		static Vector2D<_Numeric> ones()
		{
			return { 1, 1 };
		}

		double length() const { return sqrt(x * x + y * y); }
		double rotation() const { return atan2(y, x); }


		Vector2D<_Numeric> get_rotated(double rotation) const
		{
			_Numeric sin_a = sin(rotation);
			_Numeric cos_a = cos(rotation);
			return { x * cos_a - y * sin_a, x * sin_a + y * cos_a };
		}

		// geometric average of the coordinates
		double quadrature() const
		{
			return sqrt(x * y);
		}


		template <class _Numeric2> bool operator == (const Vector2D<_Numeric2> & rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		template <class _Numeric2> bool operator != (const Vector2D<_Numeric2> & rhs) const
		{
			return !(*this == rhs);
		}

		template <class _Numeric2> Vector2D<std::common_type_t<_Numeric, _Numeric2>> operator + (const Vector2D<_Numeric2> & rhs) const
		{
			return { x + rhs.x, y + rhs.y };
		}

		template <class _Numeric2> Vector2D<std::common_type_t<_Numeric, _Numeric2>> operator - (const Vector2D<_Numeric2> & rhs) const
		{
			return { x - rhs.x, y - rhs.y };
		}

		template <class _Numeric2> Vector2D<std::common_type_t<_Numeric, _Numeric2>> operator * (_Numeric2 rhs) const
		{
			return { x * rhs, y * rhs };
		}

		template <class _Numeric2> Vector2D<std::common_type_t<_Numeric, _Numeric2>> operator * (const Vector2D<_Numeric2> & rhs) const
		{
			return { x * rhs.x, y * rhs.y };
		}

		Vector2D<double> operator / (double rhs) const
		{
			return { x / rhs, y / rhs };
		}

		template <class _Numeric2> Vector2D<double> operator / (const Vector2D<_Numeric2> & rhs) const
		{
			return { double(x) / rhs.x, double(y) / rhs.y };
		}

		template <class _NewNumeric> Vector2D<_NewNumeric> cast() const
		{
			return { x, y };
		}
	};

}