
#include "PerlinSphericalKernel.hpp"

#define PI 3.1415927

PerlinSphericalKernel::PerlinSphericalKernel(float initial_radius, float p, float h, float q, PerlinSignal* signal) 
	: SphericalKernel(initial_radius, p, h, q) 
{
	m_signal = signal;
}


float PerlinSphericalKernel::noise(float alpha, float phi) 
{
	float a = alpha / PI + 0.5;
	float b = phi / PI;
	return m_signal->value(a,b);
}
