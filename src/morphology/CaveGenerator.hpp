
#ifndef HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP
#define HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP

#include "kernels/Kernel.hpp"
#include <structures/heightfield/LayeredHeightfield.hpp>

class CaveGenerator 
{
public:
	void generate(Kernel *k, LayeredHeightfield* h);
};

#endif // HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP
