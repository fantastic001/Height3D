
#ifndef HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP
#define HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP

#include "kernels/Kernel.hpp"
#include <structures/heightfield/LayeredHeightfield.hpp>

/// Make holes on terrain with given kernel specifying where holes should be made (forall x,y where defined(x,y) and bottom(x,z) < y < top(x,z))
class CaveGenerator 
{
public:
	void generate(Kernel *k, LayeredHeightfield* h);
};

#endif // HEIGHT3D_MORPHOLOGY_CAVE_GENERATOR_HPP
