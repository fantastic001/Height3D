
//#define BOOST_TEST_MODULE Functional_Scene
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

#include <loops/SDLLoop.hpp>
#include <loops/SDLEvent.hpp>

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

class MyLoop : public SDLLoop 
{

	Program program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	Scene scene;

	SceneObject* cube;

	// angle of rotation
	float alpha;

public:
	MyLoop(Window *w) : SDLLoop(w) 
	{
		glewInit();
		program.addShader(Shader(GL_VERTEX_SHADER, "functional/scene/shader.vp"));
		program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/scene/shader.fp"));
		program.link();
		program.bind();
	
		vertexLocation = program.getAttributeLocation("vPosition");
		texCoordLocation = program.getAttributeLocation("uv");
		vertexColorLocation = program.getAttributeLocation("vColor");
		samplerLocation = program.getUniformLocation("image");
		modelLocation = program.getUniformLocation("model");
		perspectiveLocation= program.getUniformLocation("perspective");
	
		program.enableAttributeArray(vertexLocation);
		program.enableAttributeArray(texCoordLocation);
		program.enableAttributeArray(vertexColorLocation);
	}
	

protected:
	void onInit() 
	{
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		scene.setPerspective(3.1415 / 2, 1.0, 0.1, 10);
		cube = scene.addObject(new SceneObject(
			new  CubeModel(), // use cube model to draw this object
			new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB), // use dummy texture 
			0.0, 0.0, 0.0, // location 
			0.0, 0.0, // angles of rotation 
			0.5, 0.5, 0.5  // size
		));
		alpha = 0.0;
	}

	void onKeyPress(Event e) 
	{
		if (e == SDLEvent::asEvent(SDLK_LEFT)) alpha -= 3.14 / 20;
		if (e == SDLEvent::asEvent(SDLK_RIGHT)) alpha += 3.14 / 20;
		scene.setCamera(0,1,0, Vector(5*cos(alpha), -1, 5*sin(alpha)), Vector(0,1,0));
	}

	void onKeyRelease(Event e) 
	{
		
	}

	void onQuit() 
	{
		SDL_Quit();
	}

	void onFrame() 
	{
		scene.drawObjects(
			&program, 
			modelLocation, 
			perspectiveLocation, 
			vertexLocation, 
			texCoordLocation, 
			vertexColorLocation, 
			samplerLocation
		);
	}
};

BOOST_AUTO_TEST_CASE( functional_scene_loop )
{

	Window win(512, 512, "tutorial");
	MyLoop loop(&win);
	loop.run();
}


