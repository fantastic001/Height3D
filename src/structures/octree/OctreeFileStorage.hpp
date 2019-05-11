
#ifndef HEIGHT3D_STRUCTURES_OCTREE_OCTREE_FILE_STORAGE_HPP
#define HEIGHT3D_STRUCTURES_OCTREE_OCTREE_FILE_STORAGE_HPP

#include "Octree.hpp"
#include <fstream>

/*!
This class provides interface to save and read Octree representation from a file. 

File is binary and has following records:
	
	float[3] start		x,y,z coordinates of starting point of bounded space by the node 
	float[3] end		x,y,z coordinates of ending point 
	bool active		specifies whether node is active or not
	bool has_childs		represents whether a node has children 

this is followed by node's childs so if we have tree like ths 

		A
		|
		-----
		|   |
		B   C

then it is represented as ABC.
*/
class OctreeFileStorage 
{

	
	std::fstream m_f;
public:
	OctreeFileStorage(char* path, bool filewrite = false);
	~OctreeFileStorage();

	void write(Octree* node);

	Octree* read();

	void close();
};

#endif // HEIGHT3D_STRUCTURES_OCTREE_OCTREE_FILE_STORAGE_HPP
