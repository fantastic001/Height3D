
#ifndef HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP
#define HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP

#include <core/Array3D.hpp>
#include "Octree.hpp"

class Array3DOctreeAdapter 
{
	Octree* m_root; 

	Octree* addChilds(Array3D<bool> arr, int startx, int endx, int starty, int endy, int startz, int endz);
public: 
	/*
	Compresses given array to octree 

	node values are 0 or 1 
	node is active if arr()i,j,k is true 
	position is indices (i,j,k) 
	*/
	Array3DOctreeAdapter(Array3D<bool> arr); 

	Octree* getRoot();
};

#endif // HEIGHT3D_STRUCTURES_ARRAY3DOCTREEADAPTER_HPP
