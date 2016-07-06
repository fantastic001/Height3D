
#include "Array3DOctreeAdapter.hpp" 
#include <cstdlib>

Octree* Array3DOctreeAdapter::addChilds(Array3D<bool> &arr, int startx, int endx, int starty, int endy, int startz, int endz) 
{
	if (endx <= startx || endy <= starty || endz <= startz) return NULL; 
	int x = (startx + endx) / 2; 
	int y = (starty + endy) / 2; 
	int z = (startz + endz) / 2;
	if (x >= arr.getSizeX() || y >= arr.getSizeY() || z >= arr.getSizeZ()) 
	{
		return NULL;
	}
	Vector position((float) x, (float) y, (float) z);
	bool active = arr(x,y,z);
	float value = active ? 1.0 : 0.0;
	Octree *node = new Octree(position,value, active);
	if (endx - startx == 1 || endy - starty == 1 || endz - startz == 1) 
	{
		
		node->setChild(false, true, false, NULL);
		node->setChild(false, true, true, NULL);
		node->setChild(false, false, false, NULL);
		node->setChild(false, false, true, NULL);

		node->setChild(true, true, false, NULL);
		node->setChild(true, true, true, NULL);
		node->setChild(true, false, false, NULL);
		node->setChild(true, false, true, NULL);

	}
	else {
		node->setChild(false, false, false, addChilds(arr, startx, x, starty, y, startz, z));
		node->setChild(false, false, true, addChilds(arr, startx, x, starty, y, z+1,  endz));
		node->setChild(false, true, false, addChilds(arr, startx, x, y+1, endy, startz, z));
		node->setChild(false, true, true, addChilds(arr, startx, x, y+1, endy, z+1, endz));
		
		node->setChild(true, false, false, addChilds(arr, x+1, endx, starty, y, startz, z));
		node->setChild(true, false, true, addChilds(arr, x+1, endx, starty, y, z+1,  endz));
		node->setChild(true, true, false, addChilds(arr, x+1, endx, y+1, endy, startz, z));
		node->setChild(true, true, true, addChilds(arr, x+1, endx, y+1, endy, z+1, endz));
	}
	return node; 
}

Array3DOctreeAdapter::Array3DOctreeAdapter(Array3D<bool> &arr)
{
	m_root = NULL;


	int sizex = arr.getSizeX();
	int sizey = arr.getSizeY(); 
	int sizez = arr.getSizeZ();
	m_root = addChilds(arr, 0, sizex, 0, sizey, 0, sizez);

}

Octree* Array3DOctreeAdapter::getRoot() 
{
	return m_root; 
}
