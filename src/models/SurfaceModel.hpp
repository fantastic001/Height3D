#ifndef HEIGHT3D_MODELS_SURFACE_MODEL_HPP
#define HEIGHT3D_MODELS_SURFACE_MODEL_HPP

#include <core/AbstractModel.hpp>

class SurfaceModel : public AbstractModel 
{

	int m_precision;

public:

	/*
	Specify precision, from precision dx and dz will be derived: dx = dz = 2 / precision
	*/
	SurfaceModel(int precision); 

protected:
	std::vector<float> genVertices(); 
	std::vector<int> genIndices();
	std::vector<float> genVertexColors();
	std::vector<float> genTextureCoordinates();
	std::vector<float> genNormals();
	
	/*
	Defines function y = f(x,z) 
	
	It should return real value for EVERY (x,z) in range [-1, 1]
	*/
	virtual float function(float x, float z) = 0;
};

#endif // HEIGHT3D_MODELS_SURFACE_MODEL_HPP
