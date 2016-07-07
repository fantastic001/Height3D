
#ifndef HEIGHT3D_STRUCTURES_OCTREE_HPP
#define HEIGHT3D_STRUCTURES_OCTREE_HPP

#include <core/Vector.hpp>

class Octree
{
	Vector m_position;
	bool m_active;
	float m_value; 
	Octree* m_childs[8];

	int getIndex(bool right, bool up, bool front);

public:
	Octree(Vector position, float value, bool active);
	~Octree();

	bool active();
	float value();
	Vector position();
	
	/*
	Do DFS starting from the root node (this object) and searching for node with given position

	If no such node is found, return NULL
	*/
	Octree* findNodeByPosition(Vector position);

	Octree* setChild(bool right, bool up, bool front, Octree* node);
	Octree* getChild(bool right, bool up, bool front);
	Octree* getChild(int index);
};

typedef Octree OctreeNode; 

#endif // HEIGHT3D_STRUCTURES_OCTREE_HPP
