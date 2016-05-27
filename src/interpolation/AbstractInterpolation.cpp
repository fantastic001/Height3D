
#include "AbstractInterpolation.hpp"



void AbstractInterpolation::addPoint(Vector x, float value) 
{
	m_points.push_back(x);
	m_values.push_back(value);
}

std::vector<Vector> AbstractInterpolation::getPoints() 
{
	return m_points; 
}

std::vector<float> AbstractInterpolation::getValues() 
{
	return m_values;
}

void AbstractInterpolation::reset() 
{
	m_points.clear();
	m_values.clear();
}

