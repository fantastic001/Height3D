
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

#include <structures/heightfield/LayeredHeightfield.hpp>

#include <terrain/TerrainPart.hpp>
#include <noise/perlin/PerlinSignal.hpp>

using namespace std;

class MyBigTerrainTestLoop : public SDLLoop 
{

	Program program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	int normalLocation, ambientProductLocation, diffuseProductLocation, specularProductLocation, lightPositionLocation, shininessLocation;
	Vector camera_position;
	Scene scene;


	// angle of rotation
	float alpha;

	// terrain description 
	PerlinSignal* m_terrain;

public:
	MyBigTerrainTestLoop(Window *w) : SDLLoop(w) 
	{
		cout << "Initializing glew\n";
		glewInit();

		cout << "Binding program\n";
		program.addShader(Shader(GL_VERTEX_SHADER, "functional/phong/shader.vp"));
		program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/phong/shader.fp"));
		program.link();
		program.bind();
		
		cout << "Getting locations of shader parameters\n";
		vertexLocation = program.getAttributeLocation("vPosition");
		texCoordLocation = program.getAttributeLocation("uv");
		vertexColorLocation = program.getAttributeLocation("vColor");
		samplerLocation = program.getUniformLocation("image");
		modelLocation = program.getUniformLocation("model");
		perspectiveLocation= program.getUniformLocation("perspective");
		normalLocation = program.getAttributeLocation("Normal");
		ambientProductLocation = program.getUniformLocation("ambientProduct");
		diffuseProductLocation = program.getUniformLocation("diffuseProduct");
		specularProductLocation = program.getUniformLocation("specularProduct");
		lightPositionLocation = program.getUniformLocation("LightPosition");
		shininessLocation = program.getUniformLocation("shininess");
		
		program.enableAttributeArray(vertexLocation);
		program.enableAttributeArray(texCoordLocation);
		program.enableAttributeArray(vertexColorLocation);
		program.enableAttributeArray(normalLocation);

		// Creating terrain
		cout << "Creating terrain field\n";
		m_terrain = new PerlinSignal();
		m_terrain->addFrequency(8, 0.5);
	}
	

protected:
	void onInit() 
	{
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));

		cout << "Creating big terrain\n";
		string int_to_char = "0123";
		for (int i = 0; i<4; i++) 
		{
			for (int j = 0; j<4; j++) 
			{
				cout << "Adding part at " << i << " " << j << endl;
				LayeredHeightfield *h = new LayeredHeightfield(128);
				h->addLevel();
				for (float x = -1; x<=1; x += 2.0 / 128) 
				{
					for (float z = -1; z<=1; z += 2.0/128) 
					{
						float xi = 0.25*i + 0.25 * 0.5 * (x+1);
						float zi = 0.25*j + 0.25 * 0.5 * (z+1);
						h->setBottom(0,x,z,-1);
						h->setTop(0, x, z, m_terrain->value(xi, zi));
					}
				}
				string path = string("big-terrain-") + string(int_to_char.substr(i,1)) + "-" + string(int_to_char.substr(j,1));
				h->writeToFile(path.c_str());
				float size = 5;
				scene.addObject(new TerrainPart(path.c_str(), 
					2*size*i, 2*size*j, // position
					size, // size
					1, // height
					Material(Color(1.0, 0, 0), Color(1,0,0), Color(0,0,0), 1,0,0,1),
					3*size // threshold
				));
			}
		}
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		scene.setPerspective(3.1415 / 2, 1.0, 0.1, 10);
		alpha = 0.0;
		cout << "Adding light\n";
		scene.addLight(new Light(0, 2, 0, // position
				Color(0.2, 0.0, 0.0), // ambient component
				Color(0.6, 0.0, 0.0), // diffuse component
				Color(0.0, 0.8, 0.9) // specular component
			),
			lightPositionLocation, ambientProductLocation, diffuseProductLocation, specularProductLocation
		); 
	}

	void onKeyPress(Event e) 
	{
		Vector direction = Vector(cos(alpha), 0, sin(alpha));
		if (e == SDLEvent::asEvent(SDLK_LEFT)) alpha -= 3.14 / 20;
		if (e == SDLEvent::asEvent(SDLK_RIGHT)) alpha += 3.14 / 20;
		if (e == SDLEvent::asEvent(SDLK_UP)) 
		{
			camera_position = camera_position + direction;
		}
		if (e == SDLEvent::asEvent(SDLK_DOWN)) 
		{
			camera_position = camera_position - direction;
		}
		scene.setCamera(camera_position.getX(),1,camera_position.getZ(), Vector(5*cos(alpha), -1, 5*sin(alpha)), Vector(0,1,0));
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
			samplerLocation,
			true, // use phong lighting model
			shininessLocation,
			normalLocation
		);
	}
};

BOOST_AUTO_TEST_CASE( functional_big_terrain )
{

	cout << "Running phong";
	Window win(512, 512, "tutorial");
	MyBigTerrainTestLoop loop(&win);
	loop.run();
}


