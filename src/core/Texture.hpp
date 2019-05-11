#ifndef HEIGHT3D_TEXTURE_HPP
#define HEIGHT3D_TEXTURE_HPP


#include <GL/glew.h>
#include <GL/gl.h>

class Texture 
{
	GLuint id; 
	GLenum type;
	int m_width, m_height, m_format;
	GLvoid* m_data;
public:
	/// initialize empty texture
	Texture();
	/// initialize texture with given properties 
	/// \param texture_type: GLenum type of texture
	/// \param width: width of given texture
	/// \param height height of given texture
	/// \param format can be GL_RGB or GL_RGBA (then sent data has to be height*width*4 dimmensionality)
	Texture(GLenum texture_type, int width, int height, GLint format = GL_RGB);
	/// initialize texture with given properties and specified data
	/// \param texture_type: GLenum type of texture
	/// \param width: width of given texture
	/// \param height height of given texture
	/// \param data which is sent to texture buffer
	/// \param format can be GL_RGB or GL_RGBA (then sent data has to be height*width*4 dimmensionality)
	Texture(GLenum texture_type, int width, int height, GLvoid *data, GLint format = GL_RGB);

	GLuint getId(); 
	GLenum getType();
	int getHeight();
	int getWidth();
	int getFormat();
	GLvoid* getData();

	Texture& operator=(Texture t);

	
	/*!
	NOTE: data has to be in the correct format data[height][width][format] where format is 3 or 4
	NOTE 2: data is array of type float
	*/
	void sendData(GLvoid* data);
	
	void bind(); 
};

#endif // HEIGHT3D_TEXTURE_HPP
