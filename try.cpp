#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include "debug.hpp"
#include "shaders.hpp"
#include "sdl_init.hpp"

#include "core/Buffer.hpp"
#include "core/Vector.hpp"

#include "gui/Window.hpp"

using namespace std; 

int main(int argc, char *argv[])
{
	Window win(512, 512, "tutorial");
	
	glClearColor ( 1.0, 0.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	win.redraw();
	win.delay(2000);
	
	glClearColor ( 0.0, 1.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	win.redraw();
	win.delay(2000);
	
	glClearColor ( 0.0, 0.0, 1.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	win.redraw();
	win.delay(2000);
	
	glewInit();
	Program program;
	program.addShader(Shader(GL_VERTEX_SHADER, "shader.vp"));
	program.addShader(Shader(GL_FRAGMENT_SHADER, "shader.fp"));
	program.link();
	program.bind();

	int loc = program.getAttributeLocation("vPosition");
	program.enableAttributeArray(loc);
	Vector vertices[3] = {
		Vector(-1.0, -1.0, 0.0, 0.0),
		Vector(1.0, -1.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0, 0.0)
	};
	GLfloat g_vertex_buffer_data[] = {

		-1.0f, -1.0f, 0.0f,

		1.0f, -1.0f, 0.0f,

		0.0f,  1.0f, 0.0f,
	
	}; 

	Buffer buf(GL_ARRAY_BUFFER);
	buf.sendData(vertices, 3, false);
	buf.bind();
	
	program.setAttributeArray(loc, 3);
	
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	
	win.redraw();
	win.delay(2000);
	
	SDL_Quit();
	
	return 0;
}
