#define BOOST_TEST_MODULE Functional_Textures
#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <core/Vector.hpp>

#include <SDL2/SDL.h>

#include "core/Program.hpp"
#include "core/Buffer.hpp"
#include "core/Vector.hpp"
#include "core/Texture.hpp"

#include "gui/Window.hpp"

#include <textures/GradientTextureFactory.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE( textures )
{

	Window win(512, 512, "tutorial");
	
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	win.redraw();
	win.delay(2000);
	
	glewInit();
	Program program;
	program.addShader(Shader(GL_VERTEX_SHADER, "functional/textures/shader.vp"));
	program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/textures/shader.fp"));
	program.link();
	program.bind();

	int loc = program.getAttributeLocation("vPosition");
	int coords_loc = program.getAttributeLocation("uv");
	int sampler_loc = program.getUniformLocation("image");
	program.enableAttributeArray(loc);
	program.enableAttributeArray(coords_loc);
	Vector vertices[3] = {
		Vector(-1.0, -1.0, 0.0, 0.0),
		Vector(1.0, -1.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0, 0.0)
	};

	float coordinates[] = {
		0.0, 1.0,
		1.0, 1.0,
		0.5, 0.0
	};

	Buffer buf(GL_ARRAY_BUFFER);
	buf.sendData(vertices, 3, false);
	buf.bind();
	
	program.setAttributeArray(loc, 3);

	Buffer coords_buffer(GL_ARRAY_BUFFER);
	coords_buffer.sendData(coordinates, 6);
	coords_buffer.bind();
	program.setAttributeArray(coords_loc, 2);

	/*float image[512][512][3];
	for (int i = 0; i<512; i++) 
	{
		for (int j = 0; j<512; j++) 
		{
			image[i][j][2] = 1.0;
			image[i][j][1] = 0;
			image[i][j][0] = j / 512.0;
		}
	}
	Texture t(GL_TEXTURE_2D, 512, 512);
	t.sendData(image);*/
	Texture t = GradientTextureFactory(Color(0, 0, 1.0), Color(1.0, 0, 0), 512, 512).getTexture();
	t.bind();

	program.setUniformValue(sampler_loc);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	
	win.redraw();
	win.delay(2000);
	
	SDL_Quit();
}


