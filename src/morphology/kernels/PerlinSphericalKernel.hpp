
#ifndef HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP
#define HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP

#include "SphericalKernel.hpp"

#include <noise/perlin/PerlinSignal.hpp>

class PerlinSphericalKernel : public SphericalKernel 
{

	PerlinSignal* m_signal;
public:
	PerlinSphericalKernel(float initial_radius, float p, float h, float q, PerlinSignal* signal);

protected:
	float noise(float alpha, float phi);
};

#endif // HEIGHT3D_MORPHOLOGY_KERNELS_PERLIN_SPHERICAL_KERNEL_HPP
