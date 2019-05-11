
#ifndef HEIGHT3D_MORPHOLOGY_SPHERICAL_KERNEL_HPP
#define HEIGHT3D_MORPHOLOGY_SPHERICAL_KERNEL_HPP

#include "Kernel.hpp"

class SphericalKernel : public Kernel 
{
	float m_radius;
	float m_p, m_q, m_h; 
public:
	/*!
	initial_radius: radius of sphere
	p: x coordinate of center
	h: y coordinate of center
	q: z coordinate of center
	*/
	SphericalKernel(float initial_radius, float p, float h, float q);

	float getInitialRadius();
	bool defined(float x, float z);

	float top(float x, float z);
	float bottom(float x, float z);

protected:
	/*

	alpha: angle in xz plane from x axis
	phi: angle in space from y axis
	*/
	virtual float noise(float alpha, float phi) = 0;
};

#endif // HEIGHT3D_MORPHOLOGY_SPHERICAL_CAVE_GENERATOR_HPP
