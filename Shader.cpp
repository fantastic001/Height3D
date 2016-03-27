#include "Shader.hpp"

#include <fstream>
#include <string> 
#include <cstdlib> 
#include <cstdio>

#include <iostream>

using namespace std; 

Shader::Shader(GLuint type, const char* path) 
{

	ifstream ifs (path);
	string s;
	getline (ifs, s, (char) ifs.eof());
	
	GLint result;
	int length = s.size();
	shader = glCreateShader(type);
	const GLchar* source = s.c_str();
	const GLchar** source_ptr = &source;
	cout << s << endl;
	glShaderSource(shader, 1, source_ptr, &length);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	
	if(result == GL_FALSE) {
		char *log;

		// get the shader info log 
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log = (char*) malloc(length);
		glGetShaderInfoLog(shader, length, &result, log);
	
		// print an error message and the info log 
		fprintf(stderr, "shaderCompileFromFile(): Unable to compile %s: %s\n", path, log);
		free(log);
	
		glDeleteShader(shader);
	}
}

Shader::~Shader() 
{
	glDeleteShader(shader); 
}

GLuint Shader::getShaderId() 
{
	return this->shader; 
}
