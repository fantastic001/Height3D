
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_MODEL_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_MODEL_HPP

#include <core/AbstractModel.hpp> 
#include "LayeredHeightfield.hpp"

class LayeredHeightfieldModel : public AbstractModel 
{

	LayeredHeightfield* m_heightfield; 
	int m_precision;

public:
	LayeredHeightfieldModel(LayeredHeightfield *heightfield);
	LayeredHeightfield* getField();

protected:

	std::vector<float> genVertices();
	
	std::vector<int> genIndices();
	
	std::vector<float> genVertexColors();
	
	std::vector<float> genTextureCoordinates();

	std::vector<float> genNormals();

	
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_MODEL_HPP
