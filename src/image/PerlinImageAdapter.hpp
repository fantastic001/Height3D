
#ifndef HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP
#define HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP


#include <noise/Perlin.hpp>

#include <vector>

class PerlinImageAdapter 
{
	std::vector<Perlin*> m_perlins;
	std::vector<float> m_amplitudes;
public:
	void addFrequency(int frequency, float amplitude);
	
	/*
	Best results are achieved if frequency = 2 * size of Perlin noise
	*/
	void saveToFile(char* filename, int frequency);

};

#endif // HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP
