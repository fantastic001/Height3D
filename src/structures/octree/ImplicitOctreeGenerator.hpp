
#ifndef HEIGHT3D_STRUCTURES_IMPLICIT_OCTREE_GENERATOR_HPP
#define HEIGHT3D_STRUCTURES_IMPLICIT_OCTREE_GENERATOR_HPP

#include "Octree.hpp"

class ImplicitOctreeGenerator 
{
	Octree* m_root; 
	Octree* addChilds(int startx, int endx, int starty, int endy, int startz, int endz);
	bool m_compress;

public:
	void generate(int precisionx, int precisiony, int precisionz, bool compress);
	Octree* getRoot();

protected:
	virtual bool isActive(int i, int j, int k) = 0;

};

#endif // HEIGHT3D_STRUCTURES_IMPLICIT_OCTREE_GENERATOR_HPP
