
#include "Program.hpp"

Program::Program() 
{
	program_id = glCreateProgram();
}


Program::~Program() 
{
	glDeleteProgram(program_id);
}

bool Program::addShader(Shader shader) 
{
	glAttachShader(program_id, shader.getShaderId());
}
	
int Program::getAttributeLocation(char* name) 
{
	return glGetAttribLocation(program_id, name);
	// TODO throw exception if returned value is -1
}
	
void Program::enableAttributeArray(int location) 
{
	glEnableVertexAttribArray(location);
}

void Program::disableAttributeArray(int location) 
{
	glDisableVertexAttribArray(location);
}

void Program::link() 
{
	glLinkProgram(program_id);
}

void Program::bind() 
{
	glUseProgram(program_id);
}

GLuint Program::getProgramId() 
{
	return program_id;
}

void Program::setAttributeArray(int location, int vertex_size)
{
	glVertexAttribPointer(
		location,
		vertex_size,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
}
	
void Program::setUniformValue(int location, GLfloat value) 
{
	glUniform1f(location, value);
}

// TODO setUniformValue for vectors and matrices 3x3 4x4 2x2 

int Program::getUniformLocation(char* name) 
{
	return glGetUniformLocation(program_id, name);
}
