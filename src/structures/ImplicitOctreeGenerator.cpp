
#include "ImplicitOctreeGenerator.hpp"

#include <cstdlib>

Octree* ImplicitOctreeGenerator::addChilds(int startx, int endx, int starty, int endy, int startz, int endz) 
{
	if (endx == startx+1 && endy == starty+1 && endz == startz+1) 
	{	
		return new OctreeNode(
			Vector(startx, starty, startz), 
			isActive(startx, starty, startz) ? 1.0 : 0.0, 
			isActive(startx, starty, startz)
		); 
	}
	int x = (startx + endx) / 2; 
	int y = (starty + endy) / 2; 
	int z = (startz + endz) / 2;
	
	Vector position((float) x, (float) y, (float) z);
	bool active = isActive(x,y,z);
	float value = active ? 1.0 : 0.0;
	Octree *node = new Octree(position,value, active);
	
	node->setChild(false, false, false, addChilds(startx, x, starty, y, startz, z));
	node->setChild(false, false, true, addChilds(startx, x, starty, y, z,  endz));
	node->setChild(false, true, false, addChilds(startx, x, y, endy, startz, z));
	node->setChild(false, true, true, addChilds(startx, x, y, endy, z, endz));
	
	node->setChild(true, false, false, addChilds(x, endx, starty, y, startz, z));
	node->setChild(true, false, true, addChilds(x, endx, starty, y, z,  endz));
	node->setChild(true, true, false, addChilds(x, endx, y, endy, startz, z));
	node->setChild(true, true, true, addChilds(x, endx, y, endy, z, endz));
	
	if (m_compress) 
	{
		bool same_all = true;
		int i;
		for (i = 0; i<8; i++) 
		{
			if (node->getChild(i) != NULL) same_all = same_all && active == node->getChild(i)->active(); 
		}
		if (same_all) 
		{
			for (i=0; i<8; i++) 
			{
				if (node->getChild(i) != NULL) node->destroyChild(i);
			}
		}
	}
	return node; 
}

void ImplicitOctreeGenerator::generate(int precisionx, int precisiony, int precisionz, bool compress)
{
	m_compress = compress;
	m_root = NULL;
	int sizex = precisionx;
	int sizey = precisiony;
	int sizez = precisionz;
	m_root = addChilds(0, sizex, 0, sizey, 0, sizez);

}

Octree* ImplicitOctreeGenerator::getRoot() 
{
	return m_root; 
}
