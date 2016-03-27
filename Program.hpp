#ifndef HEIGHT3D_PROGRAM_HPP
#define // HEIGHT3D_PROGRAM_HPP

#include "Shader.hpp"

class Program 
{
	
public:
	bool addShader(Shader shader);
	int getAttributeLocation(char* name);
	
	void enableAttributeArray(int location);
	void disableAttributeArray(int location);

	void link();

	GLuint getProgramId();

	void setAttributeArray(int location, GLenum type, std::vector<float> values, int stride = 0);
	
	void setUniformValue(int location, GLfloat value);

	// TODO setUniformValue for vectors and matrices 3x3 4x4 2x2 

	int getUniformLocation(char* name);
};

#endif // HEIGHT3D_PROGRAM_HPP
