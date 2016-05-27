
#ifndef HEIGHT3D_NOISE_PERLIN_HPP
#define HEIGHT3D_NOISE_PERLIN_HPP

#include <core/Vector.hpp>

class Perlin 
{
	Vector* m_gradients;
	int m_size;

public:
	Perlin(int size);
	~Perlin();
	
	
	float getDotProduct(int ix, int iy, float xf, float yf);
	Vector getRandomGradient();

	/*
	(0,0) <= (x,y) <= (1,1)

	Get Specified value from noise
	*/
	float getValue(float x, float y);
};

#endif // HEIGHT3D_NOISE_PERLIN_HPP
