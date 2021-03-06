
#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <Height3D/core/Vector.hpp>

#include <Height3D/core/Program.hpp>
#include <Height3D/core/Buffer.hpp>
#include <Height3D/core/Vector.hpp>
#include <Height3D/core/Texture.hpp>
#include <Height3D/core/Scene.hpp>
#include <Height3D/core/SceneObject.hpp>
#include <Height3D/core/AbstractModel.hpp>

#include <Height3D/gui/Window.hpp>

#include <Height3D/loops/SDLLoop.hpp>
#include <Height3D/loops/SDLEvent.hpp>

#include <Height3D/structures/heightfield/LayeredHeightfield.hpp>
#include <Height3D/structures/heightfield/LayeredHeightfieldModel.hpp>

using namespace std;

class MyLoop : public SDLLoop 
{

	Program *program;
	int vertexLocation, texCoordLocation, vertexColorLocation, samplerLocation, modelLocation, perspectiveLocation;
	int normalLocation, ambientProductLocation, diffuseProductLocation, specularProductLocation, lightPositionLocation, shininessLocation;
	Vector camera_position;
	Scene *scene;

	SceneObject* cube;

	// angle of rotation
	float alpha;

public:
	MyLoop(Window *w) : SDLLoop(w) 
	{

		cout << "Initializing glew\n";
		glewInit();
		cout << "Creating program\n";
		program = new Program;

		cout << "Binding program\n";
		program->addShader(Shader(GL_VERTEX_SHADER, "shader.vp"));
		program->addShader(Shader(GL_FRAGMENT_SHADER, "shader.fp"));
		program->link();
		program->bind();
		
		cout << "Getting locations of shader parameters\n";
		vertexLocation = program->getAttributeLocation("vPosition");
		texCoordLocation = program->getAttributeLocation("uv");
		vertexColorLocation = program->getAttributeLocation("vColor");
		samplerLocation = program->getUniformLocation("image");
		modelLocation = program->getUniformLocation("model");
		perspectiveLocation= program->getUniformLocation("perspective");
		normalLocation = program->getAttributeLocation("Normal");
		ambientProductLocation = program->getUniformLocation("ambientProduct");
		diffuseProductLocation = program->getUniformLocation("diffuseProduct");
		specularProductLocation = program->getUniformLocation("specularProduct");
		lightPositionLocation = program->getUniformLocation("LightPosition");
		shininessLocation = program->getUniformLocation("shininess");
		
		program->enableAttributeArray(vertexLocation);
		program->enableAttributeArray(texCoordLocation);
		program->enableAttributeArray(vertexColorLocation);
		program->enableAttributeArray(normalLocation);

	}
	

protected:
	void onInit() 
	{
		
		scene = new Scene;
		cout << "Setting up scene\n";
		scene->setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		LayeredHeightfield *h = new LayeredHeightfield(128);
		h->addLevel();
		h->addLevel();
		for (float x = -1; x<=1; x += 2.0/128) 
		{
			for (float z = -1; z<=1; z += 2.0/128) 
			{
				cout << x << " " << z << endl;
				h->setBottom(0,x,z, 0.4 * (x*x + z*z) - 1.0);
				h->setTop(0,x,z, 0.4 * (x*x + z*z));
				
				h->setBottom(1, x,z, 1.2);
				h->setTop(1, x,z, 1.4);
			}
		} 

		scene->setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		scene->setPerspective(3.1415 / 2, 1.0, 0.1, 10);
		cout << "L/R edges: " << h->countLeftRightEdges() << endl;
		cout << "F/B edges: " << h->countForwardBackwardEdges() << endl;
		cube = scene->addObject(new SceneObject(
			new  LayeredHeightfieldModel(h), 
			new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB), // use dummy texture 
			0.0, 0.0, 0.0, // location 
			0.0, 0.0, // angles of rotation 
			0.5, 0.5, 0.5,  // size
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
		scene->addLight(new Light(0, 2, 0, // position
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
		scene->setCamera(camera_position.getX(),1,camera_position.getZ(), Vector(5*cos(alpha), -1, 5*sin(alpha)), Vector(0,1,0));
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
		scene->drawObjects(
			program, 
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

int main()
{
	Window *win = new Window(512, 512, "tutorial");
	cout << "Creating loop\n";
	MyLoop *loop = new MyLoop(win);
	loop->run();
	return 0;
}


