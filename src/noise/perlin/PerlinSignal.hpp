
#ifndef HEIGHT3D_NOISE_PERLIN_PERLIN_SIGNAL_HPP
#define HEIGHT3D_NOISE_PERLIN_PERLIN_SIGNAL_HPP

#include "Perlin.hpp"
#include <vector>
class PerlinSignal 
{
	
	std::vector<Perlin*> m_perlins;
	std::vector<float> m_amplitudes;
public:
	
	~PerlinSignal();

	void addFrequency(int frequency, float amplitude);

	float value(float x, float z);
};

#endif // HEIGHT3D_NOISE_PERLIN_PERLIN_SIGNAL_HPP
