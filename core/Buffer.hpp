
#ifndef HEIGHT3D_BUFFER_HPP
#define HEIGHT3D_BUFFER_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>

#include "Vector.hpp"

class Buffer 
{
	GLuint id; 
	GLenum type;

public: 
	Buffer(GLenum _type);


	void bind();

	void sendData(std::vector<float> data);
	void sendData(Vector* data, int n, bool include_w = true);
	void sendData(float* data, int n);
};

#endif // HEIGHT3D_BUFFER_HPP
