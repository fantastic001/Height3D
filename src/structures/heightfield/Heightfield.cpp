
#include "Heightfield.hpp"
#include <cstring>
using namespace std;

Heightfield::Heightfield(int precision) 
{
	m_precision = precision; 
	m_top = new float[(m_precision + 1) * (m_precision + 1)];
	m_bottom = new float[(m_precision + 1) * (m_precision + 1)];
	N = m_precision + 1;
	for (int i = 0; i<N; i++) 
	{
		for (int j = 0; j<N; j++) 
		{
			m_top[i*(m_precision + 1) + j] = -1;
			m_bottom[i*(m_precision + 1) + j] = -1;
		}
	}
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
	setTopLevel(i,j,y);
}

void Heightfield::setBottomLevel(float x, float z, float y) 
{
	int i,j; 
	i = int((x+1) * m_precision / 2);
	j = int((z+1) * m_precision / 2);
	setBottomLevel(i,j,y);
}

void Heightfield::setTopLevel(int i, int j, float y) 
{
	m_top[i*(m_precision + 1) + j] = y;
}
void Heightfield::setBottomLevel(int i, int j, float y) 
{
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

float Heightfield::getTopLevel(int i, int j) 
{
	return m_top[i*(m_precision + 1) + j];
}

float Heightfield::getBottomLevel(int i, int j) 
{
	return m_bottom[i*(m_precision + 1) + j];
}

void Heightfield::assign(function<pair<float, float> (float, float)> f) 
{
	for (int i = 0; i<=m_precision; i++) 
	{
		for (int j = 0; j<=m_precision; j++) 
		{
			float x =  2*float(i) / m_precision - 1;
			float z =  2*float(j) / m_precision - 1;

			setBottomLevel(x,z,f(x,z).first);
			setTopLevel(x,z,f(x,z).second);
		}
	}
}
