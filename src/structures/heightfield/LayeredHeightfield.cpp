
#include "LayeredHeightfield.hpp"

#include <fstream>

using namespace std;

typedef struct 
{
	int version = 1;
	int levels;
	int precision; 
} lhf_header; 

typedef struct 
{
	float top; 
	float bottom; 
} lhf_element;

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


void LayeredHeightfield::writeToFile(const char* path) 
{
	fstream f(path, ios::out | ios::binary);
	lhf_header header;
	header.levels = levelCount();
	header.precision = getPrecision();
	f.write((char*) &header, sizeof(header));
	for (int l = 0; l<header.levels; l++) 
	{
		for (int i = 0; i<=header.precision; i++) 
		{
			for (int j = 0; j<=header.precision; j++) 
			{
				lhf_element elem;
				elem.top = getTop(l,i,j);
				elem.bottom = getBottom(l,i,j);
				f.write((char* ) &elem, sizeof(elem));
			}
		}
	}
	f.close();

}
LayeredHeightfield* LayeredHeightfield::readFromFile(const char* path) 
{
	fstream f(path, ios::in | ios::binary);
	lhf_header header;
	f.read((char*) &header, sizeof(header));
	LayeredHeightfield* h = new LayeredHeightfield(header.precision);
	for (int l = 0; l<header.levels; l++) 
	{
		h->addLevel();
		for (int i = 0; i<=header.precision; i++) 
		{
			for (int j = 0; j<=header.precision; j++) 
			{
				lhf_element elem;
				f.read((char* ) &elem, sizeof(elem));
				h->setTop(l,i,j, elem.top);
				h->setBottom(l,i,j,elem.bottom);
			}
		}
	}
	f.close();
	return h;
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

float LayeredHeightfield::getTop(int level, int i, int j) 
{
	return m_layers->at(level)->getTopLevel(i,j);
}

float LayeredHeightfield::getBottom(int level, int i, int j) 
{
	return m_layers->at(level)->getBottomLevel(i,j);
}

void LayeredHeightfield::setTop(int level, float x, float z, float y) 
{
	m_layers->at(level)->setTopLevel(x,z,y);
}

void LayeredHeightfield::setBottom(int level, float x, float z, float y) 
{
	m_layers->at(level)->setBottomLevel(x,z,y);
}
	
void LayeredHeightfield::setTop(int level, int i, int j, float y) 
{
	m_layers->at(level)->setTopLevel(i,j,y);
}
void LayeredHeightfield::setBottom(int level, int i, int j, float y) 
{
	m_layers->at(level)->setBottomLevel(i,j,y);
}

float LayeredHeightfield::toContinious(int i) 
{
	return 2*float(i) / m_precision - 1;
}

int LayeredHeightfield::getPrecision() 
{
	return m_precision;
}
