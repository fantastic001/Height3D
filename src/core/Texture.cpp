
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

Texture::Texture()
{
}

Texture& Texture::operator=(Texture t) 
{
	id = t.getId();
	type = t.getType();
	m_width = t.getWidth();
	m_height = t.getHeight();
	m_format = t.getFormat();
	m_data = t.getData();
	
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

GLuint Texture::getId() 
{
	return id;
}

GLenum Texture::getType() 
{
	return type;
}
int Texture::getHeight() 
{
	return m_height;
}
int Texture::getWidth() 
{
	return m_width;
}

int Texture::getFormat() 
{
	return m_format;
}

GLvoid* Texture::getData() 
{
	return m_data;
}
