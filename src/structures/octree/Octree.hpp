
#ifndef HEIGHT3D_STRUCTURES_OCTREE_HPP
#define HEIGHT3D_STRUCTURES_OCTREE_HPP

#include <core/Vector.hpp>

class Octree
{
	Vector m_position;
	bool m_active;
	float m_value; 
	Vector m_start, m_end;
	Octree* m_childs[8];

	int getIndex(bool right, bool up, bool front);

public:
	Octree(Vector position, float value, bool active);
	Octree(Vector position, float value, bool active, Vector start, Vector end);
	~Octree();

	bool active();
	float value();
	Vector position();
	
	Vector start();
	Vector end();
	
	/*
	Do DFS starting from the root node (this object) and searching for node with given position

	If no such node is found, return NULL
	*/
	Octree* findNodeByPosition(Vector position);

	Octree* setChild(bool right, bool up, bool front, Octree* node);
	Octree* setChild(int index, Octree* node);
	Octree* getChild(bool right, bool up, bool front);
	Octree* getChild(int index);

	void destroyChild(int index);

	bool hasChilds();
};

typedef Octree OctreeNode; 

#endif // HEIGHT3D_STRUCTURES_OCTREE_HPP
