#ifndef HEIGHT3D_MODELS_SURFACE_MODEL_HPP
#define HEIGHT3D_MODELS_SURFACE_MODEL_HPP

#include <core/AbstractModel.hpp>

/// Class which constructs model based on given function y = f(x,z) which represents height at point(x,z)
class SurfaceModel : public AbstractModel 
{

	int m_precision;
	float (*f)(float, float);

public:

	/*!
	Construct SurfaceModel with given precision.
	Specify precision, from precision dx and dz will be derived: dx = dz = 2 / precision

	If you are using this constructor, then subclass this class and override function(float, float)
	*/
	SurfaceModel(int precision); 
	/*!
	Specify precision, from precision dx and dz will be derived: dx = dz = 2 / precision

	f is function which returns surface height for every x,z in range [-1, 1]
	*/
	SurfaceModel(int precision, float (*f) (float ,float)); 

protected:
	std::vector<float> genVertices(); 
	std::vector<int> genIndices();
	std::vector<float> genVertexColors();
	std::vector<float> genTextureCoordinates();
	std::vector<float> genNormals();
	
	/*!
	Defines function y = f(x,z) 

	This class does not need to be subclassed but then function pointer has to be provided to constructor
	
	It should return real value for EVERY (x,z) in range [-1, 1]
	*/
	virtual float function(float x, float z);
};

#endif // HEIGHT3D_MODELS_SURFACE_MODEL_HPP
