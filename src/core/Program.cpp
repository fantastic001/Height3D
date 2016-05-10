
#include "common.hpp"
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
	
int Program::getAttributeLocation(const char* name) 
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

void Program::setUniformValue(int location, Matrix m) 
{
	float mat[16]; 
	int k = 0; 
	for (int i = 0; i<4; i++) 
	{
		for (int j = 0; j<4; j++) 
		{
			mat[k] = m.getElement(i,j);
			k++;
		}
	}
	glUniformMatrix4fv(location, 1, true, mat);
}

void Program::setUniformValue(int location, Vector v)
{
	float a[4] = {
			v.getX(), 
			v.getY(), 
			v.getZ(), 
			v.getW()
		};
	glUniform4fv(location, 4, a);
}

void Program::setUniformValue(int samplerLocation) 
{
	glUniform1f(samplerLocation, 0);
}

int Program::getUniformLocation(char* name) 
{
	return glGetUniformLocation(program_id, name);
}
