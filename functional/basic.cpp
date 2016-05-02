#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Functional_Basic
#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <core/Vector.hpp>

#include <SDL2/SDL.h>

#include "debug.hpp"
#include "shaders.hpp"
#include "sdl_init.hpp"

#include "core/Buffer.hpp"
#include "core/Vector.hpp"

#include "gui/Window.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE( basic )
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
	program.addShader(Shader(GL_VERTEX_SHADER, "functional/basic//shader.vp"));
	program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/basic/shader.fp"));
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
}


