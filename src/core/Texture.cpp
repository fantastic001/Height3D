
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

Texture::Texture(GLenum texture_type, int width, int height, GLvoid* data, GLint format) : Texture(texture_type, width, height, format)
{
	m_data = data;
	this->sendData(data);
}

void Texture::bind() 
{
	glBindTexture(type, id);
}

void Texture::sendData(GLvoid *data) 
{
	this->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_FLOAT, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
