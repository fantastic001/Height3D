
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_IMPLICIT_LAYERED_HEIGHTFIELD_GENERATOR_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_IMPLICIT_LAYERED_HEIGHTFIELD_GENERATOR_HPP

#include "LayeredHeightfield.hpp"

class ImplicitLayeredHeightfieldGenerator 
{
	LayeredHeightfield *m_h;
public:

	LayeredHeightfield* getField();

protected:
	virtual bool isActive(float x, float y, float z) =0;
	void generate(int precision);
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_IMPLICIT_HEIGHTFIELD_GENERATOR_HPP
