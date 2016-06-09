
#ifndef HEIGHT3D_MODELS_VOXELED_MODEL_HPP
#define HEIGHT3D_MODELS_VOXELED_MODEL_HPP

#include <core/AbstractModel.hpp>
#include <core/Array3D.hpp>
#include <core/Color.hpp>

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
	
	/*
	This function has to return Color object for any (i,j,k) 

	Specifies color for specific part of model (specific voxel)
	*/
	virtual Color voxelColor(int i, int j, int k) = 0;
};

#endif // HEIGHT3D_MODELS_VOXELED_MODEL_HPP
