#ifndef HEIGHT3D_PROGRAM_HPP
#define HEIGHT3D_PROGRAM_HPP

#include "Shader.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Color.hpp"


class Program 
{
	GLuint program_id;
public:
	Program(); 
	~Program();
	
	/// Add shader to program
	bool addShader(Shader shader);

	/// Returns attribute location for specified attribute name. Location can be passed to setUniformValue, setAttributeArray etc...
	int getAttributeLocation(const char* name);
	
	/// Enables attribute on specified location to be used in vertex shader
	void enableAttributeArray(int location);
	void disableAttributeArray(int location);
	
	/// link program's shaders and compile them
	/// \sa bind()
	void link();

	/// bind program (after linking)
	void bind(); 

	GLuint getProgramId();
	
	/// Sets attribute on specified location to currently bound buffer (last Buffer object which called bind method).
	/// \sa Buffer::bind()
	/// \sa enableAttributeArray
	void setAttributeArray(int location, int vertex_size);
	
	void setUniformValue(int location, GLfloat value);
	void setUniformValue(int location, Matrix m); 

	/*
	Sets vec4 type uniform variable in shader to specified vector
	*/
	void setUniformValue(int location, Vector v);
	
	/*!
	Sets vec4 type variable to specified color (fourth component is 1.0)
	*/
	void setUniformValue(int location, Color c);

	void setUniformValue(int samplerLocation); 

	// TODO setUniformValue for vectors and matrices 3x3 4x4 2x2 

	int getUniformLocation(char* name);
};

#endif // HEIGHT3D_PROGRAM_HPP
