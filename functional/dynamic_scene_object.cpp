
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

#include <core/DynamicSceneObject.hpp>

using namespace std;

class DynamicSceneObjectPhongCubeModel : public AbstractModel 
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

	vector<float> genNormals() 
	{
		cout << "Generating normals\n";
		float a[24] = {
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
		};
		return vector<float>(a, a+24);
	}
};

class DynamicCube : public DynamicSceneObject 
{
	SceneObject* a;
	SceneObject* b;
	DynamicSceneObjectPhongCubeModel* model;
	Texture* texture;
public:
	DynamicCube()
	{
		model = new DynamicSceneObjectPhongCubeModel();
		texture = new Texture(GL_TEXTURE_2D, 1, 1, GL_RGB);
		a = new SceneObject(
			model,
			texture,
			0.0, 0.0, 0.0,
			0.0, 0.0, 
			0.5, 0.5, 0.5,
			Material(
				Color(1, 0, 0),
				Color(1, 0, 0),
				Color(1,0,0),
				1, 0, 1,
				1
			)
		);
		b = new SceneObject(
			model,
			texture,
			0.0, 0.0, 0.0,
			0.0, 0.0, 
			0.5, 0.5, 0.5,
			Material(
				Color(0, 1, 0),
				Color(0, 1, 0),
				Color(0,1,0),
				1, 0, 1,
				1
			)
		);
	}

	SceneObject* getObject(Vector cp) 
	{
		float cx = cp.getX();
		float cz = cp.getZ();

		cout << cx << " " << cz << endl;
		if (cx*cx + cz*cz < 2) 
		{
			return a;
		}
		else 
		{
			return b;
		}

	}
};

class MyDynamicSceneLoop : public SDLLoop 
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
	MyDynamicSceneLoop(Window *w) : SDLLoop(w) 
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
		camera_position = Vector(0,1,0);
		cout << "Setting scene\n";
		scene.setCamera(0, 0, 0, Vector(0, 0.0, 1.00), Vector(0, 1, 0));
		scene.setPerspective(3.1415 / 2, 1.0, 0.1, 10);
		SceneObject *cube = scene.addObject(new DynamicCube);
		alpha = 0.0;
		cout << "Adding light\n";
		scene.addLight(new Light(0, 2, 0, // position
				Color(0.2, 0.2, 0.0), // ambient component
				Color(0.4, 0.4, 0.0), // diffuse component
				Color(0.4, 0.4, 0.9) // specular component
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

BOOST_AUTO_TEST_CASE( functional_dynamic_scene_object )
{

	cout << "Running phong";
	Window win(512, 512, "tutorial");
	MyDynamicSceneLoop loop(&win);
	loop.run();
}


