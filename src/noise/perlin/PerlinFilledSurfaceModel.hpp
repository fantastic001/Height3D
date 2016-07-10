
#ifndef HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP
#define HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP

#include <models/FilledSurfaceModel.hpp>
#include "Perlin.hpp"

#include <vector>

class PerlinFilledSurfaceModel : public FilledSurfaceModel 
{
	std::vector<Perlin*> m_perlins;
	std::vector<float> m_amplitudes;
public:
	PerlinFilledSurfaceModel(int sampling_frequency);
	~PerlinFilledSurfaceModel();

	void addFrequency(int frequency, float amplitude);

protected:
	float function_top(float x, float z);
	float function_bottom(float x, float z);
};

#endif // HEIGHT3D_NOISE_PERLIN_SURFACE_MODEL_HPP
