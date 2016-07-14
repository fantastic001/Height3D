
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
		signal->addFrequency(2, 0.5);
		signal->addFrequency(16, 0.01);
		generator = new MyLayeredVoxeledHeightfield(signal);

		voxels = new Array3D<bool>(128, 128, 128);
		generator->populateArray(voxels, 128);
		
		for (int j = 0; j<5; j++) make_hole(*voxels);
		for (int i =0; i<10; i++) (*voxels).copy(erode(*voxels));
		
		adapter = new Array3DLayeredHeightfieldAdapter(*voxels);
		adapter->generate();
		h = adapter->getField();
		cout << "Number of levels " << h->levelCount() << endl;

	}
	

protected:
	void onInit() 
	{
		LayeredHeightfieldModel *model = new  LayeredHeightfieldModel(h);
		cout << "Vertices: " << model->countVertices() << endl;
	}

	void onKeyPress(Event e) 
	{
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
	}
};

int main()
{

	cout << "Running phong\n";
	Window win(512, 512, "tutorial");
	cout << "Creating loop\n";
	MyArray3DLayeredHeightfieldTestLoop loop(&win);
	cout << "Running....\n";
	loop.run();
	return 0;
}


