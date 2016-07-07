
#include "Octree.hpp"
#include <cstdlib>

int Octree::getIndex(bool right, bool up, bool front) 
{
	int i = 0; 
	if (right) i += 1;
	if (up) i += 2 ; 
	if (front) i += 4;
	return i;
}

Octree::Octree(Vector position, float value, bool active) 
{
	for (int i = 0; i<8 ;i++) m_childs[i] = NULL;
	m_active = active; 
	m_value = value; 
	m_position = position;
}
Octree::~Octree() 
{
	for (int i = 0; i<8 ;i++) delete m_childs[i];
}


bool Octree::active() 
{
	return m_active;
}

float Octree::value() 
{
	return m_value;
}

Vector Octree::position() 
{
	return m_position;
}
	
Octree* Octree::findNodeByPosition(Vector position) 
{
	Octree* current = this; 
	while (current->position() != position && current != NULL)
	{
		bool right = current->position().getX() < position.getX();
		bool up = current->position().getY() < position.getY();
		bool front = current->position().getZ() < position.getZ();
		current = current->getChild(right, up, front);
	}
	return current; 
}

Octree* Octree::setChild(bool right, bool up, bool front, Octree* node) 
{
	return setChild(getIndex(right, up, front), node);
}

Octree* Octree::setChild(int index, Octree* node) 
{
	int i = index;
	if (m_childs[i] != NULL) delete m_childs[i];
	m_childs[i] = node;
	return m_childs[i];
}

Octree* Octree::getChild(bool right, bool up, bool front) 
{
	return m_childs[getIndex(right, up, front)];
}

Octree* Octree::getChild(int index) 
{
	return m_childs[index];
}

void Octree::destroyChild(int index) 
{
	delete m_childs[index];
	m_childs[index] = NULL;
}

bool Octree::hasChilds() 
{
	bool ok = true; 
	for (int i = 0; i<8; i++) ok = ok && m_childs[i] == NULL;
	return !ok;
}
