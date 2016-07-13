
#include "PerlinSurfaceModel.hpp"

PerlinSurfaceModel::PerlinSurfaceModel(int sampling_frequency) : SurfaceModel(2*sampling_frequency) 
{

}


void PerlinSurfaceModel::addFrequency(int frequency, float amplitude)
{
	m_signal.addFrequency(frequency, amplitude);
}

float PerlinSurfaceModel::function(float x, float z) 
{
	return m_signal.value(x,z);
}
