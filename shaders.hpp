#ifndef HEIGHT3D_SHADERS_HPP
#define HEIGHT3D_SHADERS_HPP

#include <GL/gl.h>
#include <GL/glew.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Shader.hpp"

using namespace std;

GLuint shaderCompileFromFile(GLenum type, const char *filePath);
void shaderAttachFromFile(GLuint program, GLenum type, const char *filePath);
GLuint initProgram(void);

size_t shaderLoadSource(char* buffer, const char* path) 
{
	FILE *pfile = fopen(path, "r");
	long lSize;
	// obtain file size:
	fseek (pfile , 0 , SEEK_END);
	lSize = ftell (pfile);
	rewind (pfile);

	buffer = (char*) malloc (sizeof(char)*lSize);
	cout << "lSize: " << lSize << endl;
	unsigned int result = fread (buffer,1,lSize,pfile);
	fclose (pfile);
	for (int i=0; i<result; i++) 
	{
		cout << buffer[i]; 
	}
	cout << endl;
	return result;
}

GLuint
shaderCompileFromFile(GLenum type, const char *filePath)
{

    char *source;
    GLuint shader;
    GLint length, result;

    cout << "Loading source...\n";
    // get shader source */
    length = shaderLoadSource(source, filePath);
    if(!source)
	return 0;

    cout << "Length: " << length << endl;
    GLchar shader_source[length];
    for (int i=0; i<length; i++) {
    	shader_source[i] = source[i];
        cout << source[i];
    }
    cout << endl;
    cout << "Creating memory for placing the shader\n";
    // create shader object, set the source, and compile */
    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar **)&shader_source, &length);
    glCompileShader(shader);
    free(source);

    /* make sure the compilation was successful */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
	char *log;

	/* get the shader info log */
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	log = (char*) malloc(length);
	glGetShaderInfoLog(shader, length, &result, log);

	/* print an error message and the info log */
	fprintf(stderr, "shaderCompileFromFile(): Unable to compile %s: %s\n", filePath, log);
	free(log);

	glDeleteShader(shader);
	return 0;
    }

    return shader;
}

/*
 * Compiles and attaches a shader of the
 * given type to the given program object.
 */
void
shaderAttachFromFile(GLuint program, GLenum type, const char *filePath)
{
    /* compile the shader */
    Shader shader(type, filePath);
	/* attach the shader to the program */
	glAttachShader(program, shader.getShaderId());

	/* delete the shader - it won't actually be
	 * destroyed until the program that it's attached
	 * to has been destroyed */
}

GLuint
initProgram(void)
{

    glewInit();
    GLint result;

    cout << "Creating program...\n";
    /* create program object and attach shaders */
    GLuint g_program = glCreateProgram();
    cout << "Attaching shaders\n";
    shaderAttachFromFile(g_program, GL_VERTEX_SHADER, "shader.vp");
    shaderAttachFromFile(g_program, GL_FRAGMENT_SHADER, "shader.fp");

    cout << "Linking...\n";
    /* link the program and make sure that there were no errors */
    glLinkProgram(g_program);
    glGetProgramiv(g_program, GL_LINK_STATUS, &result);
    if(result == GL_FALSE) {
	GLint length;
	char *log;

	/* get the program info log */
	glGetProgramiv(g_program, GL_INFO_LOG_LENGTH, &length);
	log = (char*) malloc(length);
	glGetProgramInfoLog(g_program, length, &result, log);

	/* print an error message and the info log */
	fprintf(stderr, "sceneInit(): Program linking failed: %s\n", log);
	free(log);

	/* delete the program */
	glDeleteProgram(g_program);
	g_program = 0;
    }
    return g_program;
}


#endif // HEIGHT3D_SHADERS_HPP
