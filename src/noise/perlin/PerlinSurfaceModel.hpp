
#ifndef HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP
#define HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP

#include <models/SurfaceModel.hpp>
#include "Perlin.hpp"

#include <vector>

class PerlinSurfaceModel : public SurfaceModel 
{
	std::vector<Perlin*> m_perlins;
	std::vector<float> m_amplitudes;
public:
	PerlinSurfaceModel(int sampling_frequency);
	~PerlinSurfaceModel();

	void addFrequency(int frequency, float amplitude);

protected:
	float function(float x, float z);
};

#endif // HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP
