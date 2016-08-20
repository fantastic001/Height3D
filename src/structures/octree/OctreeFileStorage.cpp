
#include "OctreeFileStorage.hpp"

using namespace std; 

OctreeFileStorage::OctreeFileStorage(char* path, bool filewrite) 
{
	if (filewrite) m_f.open(path, ios::out | ios::binary);
	else m_f.open(path, ios::in | ios::binary);
}
OctreeFileStorage::~OctreeFileStorage() 
{
	this->close();
}

void OctreeFileStorage::close() 
{
	m_f.close();
}

void OctreeFileStorage::write(Octree* node) 
{

	float sx,sy,sz,ex,ey,ez;
	bool active;
	bool has_childs = node->hasChilds();
	sx = node->start().getX();
	sy = node->start().getY();
	sz = node->start().getZ();

	ex = node->end().getX();
	ey = node->end().getY();
	ez = node->end().getZ();
	active = node->active();

	m_f.write((char*) &sx, sizeof(float));
	m_f.write((char*) &sy, sizeof(float));
	m_f.write((char*) &sz, sizeof(float));
	
	m_f.write((char*) &ex, sizeof(float));
	m_f.write((char*) &ey, sizeof(float));
	m_f.write((char*) &ez, sizeof(float));

	m_f.write((char*) &active, sizeof(bool));
	m_f.write((char*) &has_childs, sizeof(bool));

	if (has_childs) 
	{
		for (int i = 0; i<8; i++) 
		{
			this->write(node->getChild(i));
		}
	}
}

Octree* OctreeFileStorage::read() 
{
	float sx,sy,sz,ex,ey,ez;
	bool active;
	bool has_childs;
	m_f.read((char*) &sx, sizeof(float));
	m_f.read((char*) &sy, sizeof(float));
	m_f.read((char*) &sz, sizeof(float));
	
	m_f.read((char*) &ex, sizeof(float));
	m_f.read((char*) &ey, sizeof(float));
	m_f.read((char*) &ez, sizeof(float));

	m_f.read((char*) &active, sizeof(bool));
	m_f.read((char*) &has_childs, sizeof(bool));

	Octree* node = new Octree(Vector((sx+ex)/2, (sy+ey)/2, (sz+ez)/2), 
		active ? 1.0 : 0.0, active, Vector(sx,sy,sz), Vector(ex,ey,ez));
	if (has_childs) 
	{
		for (int i = 0; i<8; i++) 
		{
			node->setChild(i, this->read());
		}
	}
	return node;
}
