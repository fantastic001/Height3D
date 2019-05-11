
#ifndef HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP
#define HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP

/// Class used to be subclassed and to implement various kinds of kernels. 
class Kernel 
{
public:

	/// Should return is kernel defined on this coordinate
	virtual bool defined(float x, float z) = 0;
	/// Should return height of top part of kernel for specified coordinate
	virtual float top(float x, float z) = 0;
	/// Should return height of bottom part of specified kernel 
	virtual float bottom(float x, float z) = 0;
};

#endif // HEIGHT3D_MORPHOLOGY_KERNELS_KERNEL_HPP
