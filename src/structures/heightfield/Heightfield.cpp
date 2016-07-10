
#include "Heightfield.hpp"
#include <cstring>

Heightfield::Heightfield(int precision) 
{
	m_precision = precision; 
	m_top = new float[(m_precision + 1) * (m_precision + 1)];
	m_bottom = new float[(m_precision + 1) * (m_precision + 1)];
	memset(m_top, 0, (m_precision + 1) * (m_precision + 1));
	memset(m_bottom, 0, (m_precision + 1) * (m_precision + 1));
	N = m_precision + 1;
}

Heightfield::~Heightfield() 
{
	delete[] m_top;
	delete[] m_bottom;
}

void Heightfield::setTopLevel(float x, float z, float y) 
{
	int i,j; 
	i = int((x+1) * m_precision / 2);
	j = int((z+1) * m_precision / 2);
	m_top[i*(m_precision + 1) + j] = y;
}

void Heightfield::setBottomLevel(float x, float z, float y) 
{
	int i,j; 
	i = int((x+1) * m_precision / 2);
	j = int((z+1) * m_precision / 2);
	m_bottom[i*(m_precision + 1) + j] = y;
}

float Heightfield::getTopLevel(float x, float z) 
{
	int i,j; 
	i = int((x+1) * m_precision / 2);
	j = int((z+1) * m_precision / 2);
	return m_top[i*(m_precision + 1) + j];
}

float Heightfield::getBottomLevel(float x, float z) 
{
	int i,j; 
	i = int((x+1) * m_precision / 2);
	j = int((z+1) * m_precision / 2);
	return m_bottom[i*(m_precision + 1) + j];
}
