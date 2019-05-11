
#ifndef HEIGHT3D_MODELS_VOXELED_MODEL_HPP
#define HEIGHT3D_MODELS_VOXELED_MODEL_HPP

#include <core/AbstractModel.hpp>
#include <core/Array3D.hpp>
#include <core/Color.hpp>

#include <tuple>

/// Construct model which is generated from voxels. Voxels are specified as 3D array of booleans.
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
	
	/*!
	This function has to return Color object for any (i,j,k) 

	Specifies color for specific part of model (specific voxel)
	*/
	virtual Color voxelColor(int i, int j, int k) = 0;

	/*!
	Specifies voxel normal at any (i,j,k)
	*/
	virtual Vector voxelNormal(int i, int j, int k) = 0;
	
	/*!
	Specifies texture coordinates for any (i,j,k) 

	Best practice is to return tuple(u,v,u+s,v+s, u-s,v-s,u,v) if on that location is only one color. 
	Actually the best choice of texture for specific voxel is only one-color texture.
	*/
	virtual std::tuple<float, float, float, float, float, float, float, float> voxelTextureCoordinates(int i, int j, int k) = 0;
};

#endif // HEIGHT3D_MODELS_VOXELED_MODEL_HPP
