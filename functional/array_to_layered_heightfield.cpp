
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
#include <structures/heightfield/LayeredHeightfieldModel.hpp>

#include <voxel/VoxeledHeightfield.hpp>
#include <structures/heightfield/Array3DLayeredHeightfieldAdapter.hpp>

#include <morphology/erode.hpp>

#include <noise/perlin/PerlinSignal.hpp>

using namespace std;

class MyLayeredVoxeledHeightfield : public VoxeledHeightfield 
{

	PerlinSignal* m_signal;
public:
	MyLayeredVoxeledHeightfield(PerlinSignal *signal) : VoxeledHeightfield() 
	{
		m_signal = signal;
	}
protected:
	float function(float x, float z) 
	{
		return m_signal->value(x,z);
	}
};

class MyArray3DLayeredHeightfieldTestLoop : public SDLLoop 
{

	Program program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	int normalLocation, ambientProductLocation, diffuseProductLocation, specularProductLocation, lightPositionLocation, shininessLocation;
	Vector camera_position;
	Scene scene;

	SceneObject* cube;

	// angle of rotation
	float alpha;

	MyLayeredVoxeledHeightfield *generator;
	Array3DLayeredHeightfieldAdapter *adapter;
	LayeredHeightfield *h;
	Array3D<bool> *voxels;
	PerlinSignal* signal;

public:
	MyArray3DLayeredHeightfieldTestLoop(Window *w) : SDLLoop(w) 
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
		
		signal = new PerlinSignal;
		signal->addFrequency(2, 0.8);
		signal->addFrequency(16, 0.02);
		signal->addFrequency(32, 0.01);
		generator = new MyLayeredVoxeledHeightfield(signal);

		voxels = new Array3D<bool>(128, 128, 128);
		generator->populateArray(voxels, 128);
		
		for (int j = 0; j<5; j++) make_hole(*voxels);
		for (int i =0; i<30; i++) (*voxels).copy(erode(*voxels));
		
		adapter = new Array3DLayeredHeightfieldAdapter(*voxels);
		adapter->generate();
		h = adapter->getField();
		cout << "Number of levels " << h->levelCount() << endl;

	}
	

protected:
	void onInit() 
	{
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));

		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		scene.setPerspective(3.1415 / 2, 1.0, 0.1, 30);
		LayeredHeightfieldModel* model = new LayeredHeightfieldModel(h);
		cout << "Number of vertices: " << model->countVertices() << endl;
		cube = scene.addObject(new SceneObject(
			model, // use cube model to draw this object
			new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB), // use dummy texture 
			0.0, 0.0, 0.0, // location 
			0.0, 0.0, // angles of rotation 
			10, 10, 10,  // size
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

BOOST_AUTO_TEST_CASE( functional_array3d_to_layered_heightfield )
{

	cout << "Running phong";
	Window win(512, 512, "tutorial");
	MyArray3DLayeredHeightfieldTestLoop loop(&win);
	loop.run();
}


