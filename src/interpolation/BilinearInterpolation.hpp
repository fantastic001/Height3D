
#ifndef HEIGHT3D_INTERPOLATION_LINEAR_INTERPOLATION_HPP
#define HEIGHT3D_INTERPOLATION_LINEAR_INTERPOLATION_HPP


#include "AbstractInterpolation.hpp"

class BilinearInterpolation : public AbstractInterpolation
{
public:
	/*
	Only works if added points have coordinates (0,0), (0,1), (1,0), (1,1)
	*/
	float interpolate(Vector x);
};

#endif // HEIGHT3D_INTERPOLATION_BILINEAR_INTERPOLATION_HPP
