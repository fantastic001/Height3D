
#include "SphericalKernel.hpp"

#include <cmath>

SphericalKernel::SphericalKernel(float initial_radius, float p, float h, float q) 
{
	m_radius = initial_radius;
	m_p = p;
	m_h = h;
	m_q = q;
}

bool SphericalKernel::defined(float x, float z) 
{
	return (x-m_p)*(x-m_p) + (z-m_q)*(z-m_q) <= m_radius * m_radius; 
}
float SphericalKernel::top(float x, float z) 
{
	float y = m_h + sqrt(m_radius*m_radius - (x-m_p)*(x-m_p) - (z-m_q)*(z-m_q));
	float phi = acos(y);
	float theta = atan2((z-m_q),x-m_p);
	return m_h + (m_radius + noise(theta, phi)) * (m_radius + noise(theta, phi)) - (x-m_p)*(x-m_p) - (z-m_q)*(z-m_q);
}
float SphericalKernel::bottom(float x, float z) 
{
	float y = m_h - sqrt(m_radius*m_radius - (x-m_p)*(x-m_p) - (z-m_q)*(z-m_q));
	float phi = acos(y);
	float theta = atan2(z-m_q,x-m_p);
	return m_h-((m_radius + noise(theta, phi))*(m_radius + noise(theta, phi)) - (x-m_p)*(x-m_p) - (z-m_q)*(z-m_q));
}

float SphericalKernel::getInitialRadius() 
{
	return m_radius;
}
