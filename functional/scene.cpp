
#define BOOST_TEST_MODULE Functional_Scene
#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <core/Vector.hpp>

#include <SDL2/SDL.h>

#include <core/Program.hpp>
#include <core/Buffer.hpp>
#include <core/Vector.hpp>
#include <core/Texture.hpp>
#include <core/Scene.hpp>
#include <core/SceneObject.hpp>
#include <core/AbstractModel.hpp>

#include <gui/Window.hpp>

#include <cmath>

using namespace std;

class CubeModel : public AbstractModel 
{
protected: 
	std::vector<float> genVertices() 
	{
		float vertices[24] = 
		{
			// bottom face
			-1.0, -1.0, -1.0,
			1.0, -1.0, -1.0,
			-1.0, -1.0, 1.0,
			1.0, -1.0, 1.0,
			
			// top face
			-1.0, 1.0, -1.0,
			1.0, 1.0, -1.0,
			-1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
		};
		return vector<float>(vertices, vertices+24);
	}
	vector<int> genIndices() {

		int indices[36] = 
		{
			// bottom face
			0, 1, 2,
			1, 2, 3,

			// left face
			0, 2, 4,
			4, 6, 2,

			// right face
			1, 3, 5,
			5, 3, 7,

			// front face 
			0, 1, 4, 
			4, 1, 5, 

			// back face 
			2, 3, 7,
			7, 6, 2,

			// top face 
			4, 5, 6, 
			5, 6, 7
		};
		return vector<int>(indices, indices+36);
	}

	vector<float> genTextureCoordinates() {

		float textures[16] = {
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
			0.0, 0.0,
		};
		return vector<float>(textures, textures+16);
	}

	vector<float> genVertexColors() {

		float colors[32] = 
		{
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,
			
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0
		};
		return vector<float>(colors, colors+32);
	}
};

BOOST_AUTO_TEST_CASE( scene )
{

	Window win(512, 512, "tutorial");
	
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );
	win.redraw();
	win.delay(2000);
	
	glewInit();
	
	Program program;
	program.addShader(Shader(GL_VERTEX_SHADER, "functional/scene/shader.vp"));
	program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/scene/shader.fp"));
	program.link();
	program.bind();

	int vertexLocation = program.getAttributeLocation("vPosition");
	int texCoordLocation = program.getAttributeLocation("uv");
	int vertexColorLocation = program.getAttributeLocation("vColor");
	int samplerLocation = program.getUniformLocation("image");
	int modelLocation = program.getUniformLocation("model");
	int perspectiveLocation= program.getUniformLocation("perspective");

	program.enableAttributeArray(vertexLocation);
	program.enableAttributeArray(texCoordLocation);
	program.enableAttributeArray(vertexColorLocation);

	Scene scene;
	scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
	scene.setPerspective(3.1415 / 2, 1.0, 0.1, 10);
	
	SceneObject* cube = scene.addObject(new SceneObject(
		new  CubeModel(), // use cube model to draw this object
		new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB), // use dummy texture 
		0.0, 0.0, 0.0, // location 
		0.0, 0.0, // angles of rotation 
		0.5, 0.5, 0.5  // size
	));
	float alpha = 0.0; 
	for (int i = 0; i<60; i++) 
	{
		glClearColor ( 0.0, 0.0, 0.0, 1.0 );
		glClear ( GL_COLOR_BUFFER_BIT );
		alpha += 3.14 / 20;
		scene.setCamera(0,1,0, Vector(5*cos(alpha), -1, 5*sin(alpha)), Vector(0,1,0));
		scene.drawObjects(&program, modelLocation, perspectiveLocation, vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation);
		win.redraw();
		win.delay(30);
	}
	
	SDL_Quit();
}


