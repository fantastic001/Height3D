
#ifndef HEIGHT3D_SHADER_HPP
#define HEIGHT3D_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>


class Shader 
{
	std::string source;
	GLuint shader; 
	GLuint type;
public: 
	Shader(GLuint type, const char* path);
	~Shader();
	
	GLuint getShaderId();
};

#endif // HEIGHT3D_SHADER_HPP
