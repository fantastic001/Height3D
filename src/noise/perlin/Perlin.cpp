
#include "Perlin.hpp"
#include <interpolation/BilinearInterpolation.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;

float lerp(float a0, float a1, float w) 
{
	w = w * w * w * (w * (6*w - 15) + 10);
	//if (0.0 > w) w = -w;
	//if (w > 1.0) w=0.9;
	return (1.0 - w)*a0 + w*a1;
}

Perlin::Perlin(int size)
{
	m_size = size; 
	m_gradients = (Vector*) malloc(sizeof(Vector) * (m_size + 1) * (m_size + 1));
	for (int i = 0; i<=m_size; i++) 
	{
		for (int j = 0; j<=m_size; j++) 
		{
			m_gradients[i*(m_size + 1) + j] = getRandomGradient();
		}
	}
}
Perlin::~Perlin() 
{
	free(m_gradients);
}

float Perlin::getDotProduct(int ix, int iy, float xf, float yf)
{
	float dx = xf - (float)ix;
	float dy = yf - (float)iy;

	
	float res = Vector(dx,dy,0, 0).normalized().dot(m_gradients[iy*(m_size + 1) + ix]);
	return res;

}

float Perlin::getValue(float x, float y) 
{
	int ix = (int) (m_size) * x;
	int iy = (int) (m_size) * y;

	int x0 = ix;
	int x1 = x0 + 1; 
	int y0 = iy;
	int y1 = y0 + 1;
	float sx = (x * (m_size)) - (float)x0;
	float sy = (y * (m_size)) - (float)y0;
	float n0, n1, ix0, ix1, value;
	n0 = getDotProduct(x0, y0, x*(m_size), y*(m_size));
	n1 = getDotProduct(x1, y0, x*m_size, y*m_size);
	ix0 = lerp(n0, n1, sx);
	n0 = getDotProduct(x0, y1, x*m_size, y*m_size);
	n1 = getDotProduct(x1, y1, x*m_size, y*m_size);
	ix1 = lerp(n0, n1, sx);
	value = lerp(ix0, ix1, sy);
	return value;
}

Vector Perlin::getRandomGradient() 
{
	Vector gradients[4] = {
		Vector(1, 1, 0, 0),
		Vector(-1, 1, 0, 0),
		Vector(1,-1, 0, 0),
		Vector(-1,-1,0, 0)
	};
	srand(time(NULL));
	return gradients[rand() % 4].normalized();
}
