
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

#include <models/VoxeledModel.hpp>

#include <voxel/VoxeledHeightfield.hpp>

using namespace std;


class VoxeledTerrainModel : public VoxeledModel 
{
public:
	VoxeledTerrainModel(Array3D<bool> & a) : VoxeledModel(a) 
	{

	}
protected:
	Color voxelColor(int i, int j, int k) 
	{
		return Color(1.0, 0,0,1.0);
	}
	tuple<float, float, float, float, float, float, float, float> voxelTextureCoordinates(int i, int j, int k) 
	{
		return tuple<float, float, float, float, float, float, float, float>(0,0,0,0,0,0,0,0);
	}

	Vector voxelNormal(int i, int j, int k) 
	{
		return Vector(1.0,0,0);
	}
};

class TerrainGenerator : public VoxeledHeightfield 
{
protected:
	float function(float x, float z) 
	{
		if (x < 0) return 0; 
		else return x;
	}
};

class MyVoxeledTerrainTestLoop : public SDLLoop
{

	Program program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	int normalLocation, ambientProductLocation, diffuseProductLocation, specularProductLocation, lightPositionLocation, shininessLocation;
	Scene scene;

	SceneObject* cube;

	// angle of rotation
	float alpha;
	Vector camera_position;

public:
	MyVoxeledTerrainTestLoop(Window *w) : SDLLoop(w) 
	{
		cout << "Initializing glew\n";
		glewInit();

		cout << "Binding program\n";
		program.addShader(Shader(GL_VERTEX_SHADER, "functional/scene/shader.vp"));
		program.addShader(Shader(GL_FRAGMENT_SHADER, "functional/scene/shader.fp"));
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
		
		cout <<  program.getAttributeLocation("vPosition")<< endl;
		cout <<  program.getAttributeLocation("uv")<< endl;
		cout <<  program.getAttributeLocation("vColor")<< endl;
		cout <<  program.getUniformLocation("image")<< endl;
		cout <<  program.getUniformLocation("model")<< endl;
		cout <<  program.getUniformLocation("perspective")<< endl;
		cout <<  program.getAttributeLocation("Normal")<< endl;
		cout <<  program.getUniformLocation("ambientProduct")<< endl;
		cout <<  program.getUniformLocation("diffuseProduct")<< endl;
		cout <<  program.getUniformLocation("specularProduct")<< endl;
		cout <<  program.getUniformLocation("LightPosition")<< endl;
		cout <<  program.getUniformLocation("shininess")<< endl;
		
		cout << "Normal location: " << normalLocation << endl;

		program.enableAttributeArray(vertexLocation);
		program.enableAttributeArray(texCoordLocation);
		program.enableAttributeArray(vertexColorLocation);
		program.enableAttributeArray(normalLocation);
	}
	

protected:
	void onInit() 
	{
		cout << "Setting scene\n";
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		camera_position = Vector(0,1,0);
		scene.setPerspective(3.1415 / 2, 1.0, 0.1, 10);
		
		
		TerrainGenerator generator;
		Array3D<bool> voxels = generator.generateArray(128);
		VoxeledModel* model = new VoxeledTerrainModel(voxels);
		cube = scene.addObject(new SceneObject(
			model, 
			new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB), // use dummy texture 
			0.0, 0.0, 0.0, // location 
			0.0, 0.0, // angles of rotation 
			1.0, 1.0, 1.0,  // size
			Material(
				Color(1.0,0,0), // ambiental conductivity
				Color(1.0, 0, 0), // diffusional conductivity
				Color(1.0, 0, 0), // specular conductivity
				2, 1, 0.2, // diffusion params
				1 // shininess
			)
		));
		alpha = 0.0;
		cout << "Adding light\n";
		scene.addLight(new Light(0, 2, 0, // position
				Color(0.2, 0.0, 0.0), // ambient component
				Color(0.4, 0.0, 0.0), // diffuse component
				Color(0.4, 0.8, 0.9) // specular component
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
		cout << "Drawing\n";
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

BOOST_AUTO_TEST_CASE( functional_voxeled_terrain )
{

	cout << "Running phong";
	Window win(512, 512, "tutorial");
	MyVoxeledTerrainTestLoop loop(&win);
	loop.run();
}


