#ifndef HEIGHT3D_TEXTURE_HPP
#define HEIGHT3D_TEXTURE_HPP


#include <GL/glew.h>
#include <GL/gl.h>

class Texture 
{
	GLuint id; 
	GLenum type;
	int m_width, m_height, m_format;
public:
	Texture(GLenum texture_type, int width, int height, GLint format = GL_RGB);
	
	/*
	NOTE: data has to be in the correct format data[width][height][format] where format is 3 or 4
	*/
	void sendData(GLvoid* data);
	
	void bind(); 
};

#endif // HEIGHT3D_TEXTURE_HPP