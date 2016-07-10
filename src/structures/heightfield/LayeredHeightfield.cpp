
#include "LayeredHeightfield.hpp"


LayeredHeightfield::LayeredHeightfield(int precision) 
{
	m_precision = precision;
	m_layers = new std::vector<Heightfield*>;
}

LayeredHeightfield::~LayeredHeightfield() 
{
	for (int i = 0; i<m_layers->size(); i++) 
	{
		delete m_layers->at(i);
	}
	delete m_layers;
}

Heightfield* LayeredHeightfield::levelAt(int index) 
{
	return m_layers->at(index);
}
int LayeredHeightfield::levelCount() 
{
	return m_layers->size();
}
void LayeredHeightfield::addLevel() 
{
	m_layers->push_back(new Heightfield(m_precision));
}
void LayeredHeightfield::set(int level, float x, float z, float yb,float yt) 
{
	setTop(level, x,z,yt);
	setBottom(level, x,z,yb);
}

float LayeredHeightfield::getTop(int level, float x, float z) 
{
	return m_layers->at(level)->getTopLevel(x,z);
}

float LayeredHeightfield::getBottom(int level, float x, float z) 
{
	return m_layers->at(level)->getBottomLevel(x,z);
}

void LayeredHeightfield::setTop(int level, float x, float z, float y) 
{
	m_layers->at(level)->setTopLevel(x,z,y);
}

void LayeredHeightfield::setBottom(int level, float x, float z, float y) 
{
	m_layers->at(level)->setBottomLevel(x,z,y);
}

int LayeredHeightfield::getPrecision() 
{
	return m_precision;
}
