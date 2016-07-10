#ifndef HEIGHT3D_MODELS_SURFACE_MODEL_HPP
#define HEIGHT3D_MODELS_SURFACE_MODEL_HPP

#include <core/AbstractModel.hpp>

class FilledSurfaceModel : public AbstractModel 
{

	int m_precision;

public:

	/*
	Specify precision, from precision dx and dz will be derived: dx = dz = 2 / precision
	*/
	FilledSurfaceModel(int precision); 

protected:
	std::vector<float> genVertices(); 
	std::vector<int> genIndices();
	std::vector<float> genVertexColors();
	std::vector<float> genTextureCoordinates();
	std::vector<float> genNormals();
	
	/*
	Defines function y = f(x,z) for up part of surface
	
	It should return real value for EVERY (x,z) in range [-1, 1]
	*/
	virtual float function_top(float x, float z) = 0;

	/*
	Defines function y = f(x,z) for down part of surface
	
	It should return real value for EVERY (x,z) in range [-1, 1]
	and function_bottom(x,z) <= function_top(x,z)
	*/
	virtual float function_bottom(float x, float z) =0;
};

#endif // HEIGHT3D_MODELS_SURFACE_MODEL_HPP
