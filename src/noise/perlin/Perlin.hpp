
#ifndef HEIGHT3D_NOISE_PERLIN_HPP
#define HEIGHT3D_NOISE_PERLIN_HPP

#include <core/Vector.hpp>

#include <noise/noise.h>

class Perlin 
{
	int m_size;
	noise::module::Perlin m_noise;


public:
	Perlin(int size);
	~Perlin();
	
	
	/*!
	(0,0) <= (x,y) <= (1,1)

	Get Specified value from noise
	*/
	float getValue(float x, float y);
};

#endif // HEIGHT3D_NOISE_PERLIN_HPP
