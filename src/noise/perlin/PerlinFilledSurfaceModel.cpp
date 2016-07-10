
#include "PerlinFilledSurfaceModel.hpp"

PerlinFilledSurfaceModel::PerlinFilledSurfaceModel(int sampling_frequency) : FilledSurfaceModel(2*sampling_frequency) 
{

}

PerlinFilledSurfaceModel::~PerlinFilledSurfaceModel() 
{
	for (int i = 0; i<m_perlins.size(); i++) 
	{
		delete m_perlins.at(i);
	}
}

void PerlinFilledSurfaceModel::addFrequency(int frequency, float amplitude)
{
	m_perlins.push_back(new Perlin(frequency));
	m_amplitudes.push_back(amplitude);
}

float PerlinFilledSurfaceModel::function_top(float x, float z) 
{
	float v = 0; 
	for (int i = 0; i<m_perlins.size(); i++) 
	{
		v += m_amplitudes.at(i) * m_perlins.at(i)->getValue(0.5*(x + 1),0.5*(z + 1));
	}
	return v;
}

float PerlinFilledSurfaceModel::function_bottom(float x, float z) 
{
	return -1;
}
