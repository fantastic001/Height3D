
#ifndef HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP
#define HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP

#include <core/Vector.hpp>
#include <vector>
class AbstractInterpolation 
{

	std::vector<Vector> m_points;
	std::vector<float> m_values;
public:
	
	void addPoint(Vector x, float value);
	std::vector<Vector> getPoints();
	std::vector<float> getValues();
	
	/*
	Clears added data
	*/
	void reset();

	virtual float interpolate(Vector x) = 0;
};

#endif // HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP
