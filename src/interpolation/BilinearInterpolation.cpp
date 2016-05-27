
#include "BilinearInterpolation.hpp"

float BilinearInterpolation::interpolate(Vector x) 
{
	float f00 = getValues().at(0);
	float f01 = getValues().at(1);
	float f10 = getValues().at(2);
	float f11 = getValues().at(3);

	return f00 * (1 - x.getX())*(1 - x.getY()) 
		+ f10 * x.getX() * (1 - x.getY()) 
		+ f01 * x.getY() * (1 - x.getX())
		+ f11 * x.getX() * x.getY();
}
