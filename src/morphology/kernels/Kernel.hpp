
#ifndef HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP
#define HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP

class Kernel 
{
public:
	virtual bool defined(float x, float z) = 0;
	virtual float top(float x, float z) = 0;
	virtual float bottom(float x, float z) = 0;
};

#endif // HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP
