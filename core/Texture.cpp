
#include "common.hpp"

#include "Texture.hpp"

using namespace std; 

Texture::Texture(GLenum texture_type, int width, int height, GLint format)
{	
	glGenTextures(1, &id);
	type = texture_type;
	m_width = width; 
	m_height = height;
	m_format = format;
}

void Texture::bind() 
{
	glBindTexture(type, id);
}

void Texture::sendData(GLvoid *data) 
{
	this->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
