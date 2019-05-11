
#ifndef HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP
#define HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP

#include <core/Array3D.hpp>
#include "Octree.hpp"

#include "ImplicitOctreeGenerator.hpp"

/// Convertvoxel model representation into Octree representation
class Array3DOctreeAdapter : public ImplicitOctreeGenerator
{
	Array3D<bool> *m_arr; 
public: 
	Array3DOctreeAdapter(Array3D<bool> &arr, bool compress=false);
	
	using ImplicitOctreeGenerator::generate;
	void generate(bool compress=false);

protected:
	
	bool isActive(int i, int j, int k);
};

#endif // HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP
