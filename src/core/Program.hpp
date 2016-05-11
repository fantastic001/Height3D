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

	bool addShader(Shader shader);
	int getAttributeLocation(const char* name);
	
	void enableAttributeArray(int location);
	void disableAttributeArray(int location);

	void link();
	void bind(); 

	GLuint getProgramId();

	void setAttributeArray(int location, int vertex_size);
	
	void setUniformValue(int location, GLfloat value);
	void setUniformValue(int location, Matrix m); 

	/*
	Sets vec4 type uniform variable in shader to specified vector
	*/
	void setUniformValue(int location, Vector v);
	
	/*
	Sets vec4 type variable to specified color (fourth component is 1.0)
	*/
	void setUniformValue(int location, Color c);

	void setUniformValue(int samplerLocation); 

	// TODO setUniformValue for vectors and matrices 3x3 4x4 2x2 

	int getUniformLocation(char* name);
};

#endif // HEIGHT3D_PROGRAM_HPP
