
#include "PerlinSignal.hpp"


PerlinSignal::~PerlinSignal() 
{
	for (int i = 0; i<m_perlins.size(); i++) 
	{
		delete m_perlins.at(i);
	}
}

void PerlinSignal::addFrequency(int frequency, float amplitude)
{
	m_perlins.push_back(new Perlin(frequency));
	m_amplitudes.push_back(amplitude);
}

float PerlinSignal::value(float x, float z) 
{
	float v = 0; 
	for (int i = 0; i<m_perlins.size(); i++) 
	{
		v += m_amplitudes.at(i) * m_perlins.at(i)->getValue(0.5*(x + 1),0.5*(z + 1));
	}
	return v;
}
