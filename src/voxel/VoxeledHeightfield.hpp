
#ifndef HEIGHT3D_VOXEL_VOXELED_HEIGHTFIELD_HPP
#define HEIGHT3D_VOXEL_VOXELED_HEIGHTFIELD_HPP

#include <core/Array3D.hpp> 
#include <structures/octree/Octree.hpp>
#include <structures/octree/ImplicitOctreeGenerator.hpp>

class VoxeledHeightfield : public ImplicitOctreeGenerator
{

	int m_precision;
public:
	Array3D<bool> generateArray(int precision);
	Octree* generateOctree(int depth);

	bool isActive(int i, int j, int k);

protected:
	/*
	Specified values have to be between -1 and 1 and returned value should be between -1 and 1 
	*/
	virtual float function(float x, float z) = 0;
};

#endif // HEIGHT3D_VOXEL_VOXELED_HEIGHTFIELD_HPP
