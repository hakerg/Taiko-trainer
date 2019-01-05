#include "Transformation.h"

namespace uc
{

	Transformation::Transformation()
	{
	}


	Transformation::~Transformation()
	{
	}

	// scale dimension to fit target size

	double Transformation::fit_dimension(double dimension, double source_size, double target_size)
	{
		return dimension * target_size / source_size;
	}

}