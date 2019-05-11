
#ifndef HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP
#define HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP

#include "SphericalKernel.hpp"

#include <noise/perlin/PerlinSignal.hpp>

/// Construct kernel which is spherical where radius is determined by perlin noise
class PerlinSphericalKernel : public SphericalKernel 
{

	PerlinSignal* m_signal;
public:
	/*!
	\param initial_radius radius of sphere
	\param p x coordinate of center
	\param h y coordinate of center
	\param q z coordinate of center
	\param signal PerlinSignal object representing actual signal
	*/
	PerlinSphericalKernel(float initial_radius, float p, float h, float q, PerlinSignal* signal);

protected:
	float noise(float alpha, float phi);
};

#endif // HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP
