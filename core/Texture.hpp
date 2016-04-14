#ifndef HEIGHT3D_TEXTURE_HPP
#define HEIGHT3D_TEXTURE_HPP


#include <GL/glew.h>
#include <GL/gl.h>

class Texture 
{
	int id; 
	GLenum type;
public:
	
	void bind(); 
};

#endif // HEIGHT3D_TEXTURE_HPP
