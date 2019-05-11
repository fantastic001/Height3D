
#ifndef HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP
#define HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP

#include <core/Vector.hpp>
#include <vector>

/// Implements abstract class for implementing various kinds of interpolations 
class AbstractInterpolation 
{

	std::vector<Vector> m_points;
	std::vector<float> m_values;
public:
	
	/// add point to array of points for interpolation and value f(x) for that point
	void addPoint(Vector x, float value);

	/// Returns all points for which interpolation is done
	std::vector<Vector> getPoints();

	/// Returns all y's for points in the same order i.e. getPoints()[0] corresponds to getValues()[0]
	std::vector<float> getValues();
	
	/*!
	Clears added data
	*/
	void reset();
	
	/*!
	 * Function to be implemented which evaluates function f(x) for given x. Keep in mind that x may not be in added points. This parameter is evaluated
	 * based on interpolation function.
	 * */
	virtual float interpolate(Vector x) = 0;
};

#endif // HEIGHT3D_INTERPOLATION_ABSTRACT_INTERPOLATION_HPP
