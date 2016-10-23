
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
#include <core/TextureAtlas.hpp>
#include <textures/GradientTextureFactory.hpp>

using namespace std;

class AtlasCubeModel : public AbstractModel 
{


	TextureAtlas *atlas;
public:
	AtlasCubeModel(TextureAtlas *t) 
	{
		atlas = t;
	}
protected: 
	std::vector<float> genVertices() 
	{
		float vertices[72] = 
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
			
			// left face
			-1.0, -1.0, -1.0,
			-1.0, -1.0, 1.0,
			-1.0, 1.0, -1.0,
			-1.0, 1.0, 1.0,
			
			// right face
			1.0, -1.0, -1.0,
			1.0, -1.0, 1.0,
			1.0, 1.0, -1.0,
			1.0, 1.0, 1.0,
			
			// front face
			-1.0, -1.0, -1.0,
			-1.0, 1.0, -1.0,
			1.0, -1.0, -1.0,
			1.0, 1.0, -1.0,
			
			// back face
			-1.0, -1.0, 1.0,
			-1.0, 1.0, 1.0,
			1.0, -1.0, 1.0,
			1.0, 1.0, 1.0,
			

		};
		return vector<float>(vertices, vertices+72);
	}
	vector<int> genIndices() {

		int indices[36] = 
		{
			0,1,2,
			1,2,3,

			4,5,6,
			5,6,7,

			8,9,10,
			9,10,11,

			12,13,14,
			13,14,15,

			16,17,18,
			17,18,19,

			20,21,22,
			21,22,23

		};
		return vector<int>(indices, indices+36);
	}

	vector<float> genTextureCoordinates() {

		float textures[48] = {
			atlas->getX(0, 0), atlas->getY(0, 0),
			atlas->getX(0, 1.0), atlas->getY(0, 0),
			atlas->getX(0, 0), atlas->getY(0,1),
			atlas->getX(0, 1), atlas->getY(0,1),
			
			atlas->getX(0, 0), atlas->getY(0, 0),
			atlas->getX(0, 1.0), atlas->getY(0, 0),
			atlas->getX(0, 0), atlas->getY(0,1),
			atlas->getX(0, 1), atlas->getY(0,1),
			
			atlas->getX(1, 0), atlas->getY(1, 0),
			atlas->getX(1, 1.0), atlas->getY(1, 0),
			atlas->getX(1, 0), atlas->getY(1,1),
			atlas->getX(1, 1), atlas->getY(1,1),

			atlas->getX(1, 0), atlas->getY(1, 0),
			atlas->getX(1, 1.0), atlas->getY(1, 1.0),
			atlas->getX(1, 0), atlas->getY(1, 1),
			atlas->getX(1, 1), atlas->getY(1,1),

			atlas->getX(1, 0), atlas->getY(1, 0),
			atlas->getX(1, 1.0), atlas->getY(1, 0),
			atlas->getX(1, 0), atlas->getY(1,1),
			atlas->getX(1, 1), atlas->getY(1,1),

			atlas->getX(1, 0), atlas->getY(1, 0),
			atlas->getX(1, 1.0), atlas->getY(1, 0),
			atlas->getX(1, 0), atlas->getY(1,1),
			atlas->getX(1, 1), atlas->getY(1,1)

		};
		return vector<float>(textures, textures+48);
	}

	vector<float> genVertexColors() {

		float colors[96] = 
		{
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,
			
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,

			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,

			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,

			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,

			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0
		};
		return vector<float>(colors, colors+96);
	}
};

class MyAtlasLoop : public SDLLoop 
{

	Program program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	Scene scene;

	SceneObject* cube;

	// angle of rotation
	float alpha;

public:
	MyAtlasLoop(Window *w) : SDLLoop(w) 
	{
		glewInit();
		program.addShader(Shader(GL_VERTEX_SHADER, "functional/scene_textures/shader.vp"));
		program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/scene_textures/shader.fp"));
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
		TextureAtlas *atlas = new TextureAtlas;
		GradientTextureFactory fac(Color(1.0,0,0), Color(0,1,0), 128, 128, false);
		GradientTextureFactory fac2(Color(0.0,0,1), Color(0,1,0), 128, 128, true);
		atlas->addTexture(fac.getTexture());
		atlas->addTexture(fac2.getTexture());
		Texture tex = atlas->generateAtlas();
		cube = scene.addObject(new SceneObject(
			new  AtlasCubeModel(atlas), // use cube model to draw this object
			&tex,
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

BOOST_AUTO_TEST_CASE( functional_atlas )
{

	Window win(512, 512, "tutorial");
	MyAtlasLoop loop(&win);
	loop.run();
}


