
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
	/// Create new buffer with given type
	/// \param _type GLenum specified type
	Buffer(GLenum _type);

	/// bind buffer
	void bind();

	void sendData(std::vector<float> data);
	void sendData(std::vector<int> data);
	void sendData(Vector* data, int n, bool include_w = true);
	void sendData(std::vector<Vector> data, bool include_w = true);
	void sendData(float* data, int n);
	void sendData(int* data, int n);
};

#endif // HEIGHT3D_BUFFER_HPP
