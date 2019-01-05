#pragma once
#include "Rectangle.h"
#include "Vector2D.h"

namespace uc
{

	// use this class to convert points and vectors to another coordinate systems
	class Transformation
	{
	public:
		Transformation();
		virtual ~Transformation();

		// scale dimension to fit target size
		static double fit_dimension(double dimension, double source_size, double target_size);

		// transform position to fit target bounds
		template <class _NumericVector, class _NumericSource, class _NumericTarget>
		static Vector2D<double> fit_position(
			const Vector2D<_NumericVector> & position,
			const Rectangle<_NumericSource> & source_bounds,
			const Rectangle<_NumericTarget> & target_bounds)
		{
			return (position - source_bounds.center) * target_bounds.size / source_bounds.size + target_bounds.center;
		}

		// scale vector to fit target size
		template <class _NumericVector, class _NumericSource, class _NumericTarget>
		static Vector2D<double> fit_vector(
			const Vector2D<_NumericVector> & vector,
			const Vector2D<_NumericSource> & source_size,
			const Vector2D<_NumericTarget> & target_size)
		{
			return vector * target_size / source_size;
		}
	};

}