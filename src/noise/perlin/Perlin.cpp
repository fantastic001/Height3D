
#include "Perlin.hpp"
#include <interpolation/BilinearInterpolation.hpp>
#include <cstdlib>
#include <ctime>

#include <noise/noise.h>

using namespace noise; 
using namespace std;



Perlin::Perlin(int size)
{
	srand(time(NULL));
	m_size = size; 
	m_noise.SetOctaveCount (1);
	m_noise.SetFrequency (m_size);
}
Perlin::~Perlin() 
{
}


float Perlin::getValue(float x, float y) 
{
	return m_noise.GetValue(x,y, 0.5);
}

