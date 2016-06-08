
#ifndef HEIGHT3D_MODELS_VOXELED_MODEL_HPP
#define HEIGHT3D_MODELS_VOXELED_MODEL_HPP

#include <core/AbstractModel.hpp>
#include <core/Array3D.hpp>

class VoxeledModel : public AbstractModel 
{
	Array3D<bool> m_array; 

public:
	VoxeledModel(Array3D<bool> &array);
protected:

	std::vector<float> genVertices(); 
	
	std::vector<int> genIndices(); 
	
	std::vector<float> genVertexColors();
	
	std::vector<float> genTextureCoordinates();

	std::vector<float> genNormals();
};

#endif // HEIGHT3D_MODELS_VOXELED_MODEL_HPP
