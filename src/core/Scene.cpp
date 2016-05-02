
#include "common.hpp"
#include "Scene.hpp"

#include <cmath>

using namespace std;

Scene::Scene() 
{
}

Scene::~Scene() 
{
	for (int i = 0; i<m_objects.size(); i++) 
	{
		delete m_objects.at(i);
	}
}

SceneObject* Scene::addObject(SceneObject* object) 
{
	m_objects.push_back(object);
	return object;
}

void Scene::setCamera(float x, float y, float z, Vector direction, Vector up) 
{
	m_cx = x; 
	m_cy = y; 
	m_cz = z;
	m_direction = direction;
	m_up = up;
}

void Scene::setPerspective(float fovy, float aspect, float near, float far) 
{
	m_fovy = fovy;
	m_aspect = aspect; 
	m_near = near; 
	m_far = far;
}

Matrix Scene::getPerspectiveMatrix(float x, float y, float z, Vector direction, Vector up, float fovy, float aspect, float near, float far) 
{
	// first we set camera params
	direction = direction.normalized();
	Vector normal = direction.cross(up).normalized();
	Vector u = normal.cross(direction).normalized();
	direction = Vector(-direction.getX(), -direction.getY(), -direction.getZ());
	Vector eye(x,y,z);
	Matrix camera(
		normal.getX(), normal.getY(), normal.getZ(), -normal.dot(eye),
		u.getX(), u.getY(), u.getZ(), -u.dot(eye), 
		direction.getX(), direction.getY(), direction.getZ(), -direction.dot(eye),
		0, 0, 0, 1
	);
	
	float f = 1.0 / tan(fovy / 2);
	float d = far - near;
	Matrix perspective(
		f/aspect, 0.0, 0, 0, 
		0.0, f, 0.0, 0.0,
		0.0, 0.0, -(near + far)/d, -2*near*far/d, 
		0.0, 0.0, -1, 0.0
	);
	Matrix result = perspective.mult(camera);
	return result;
}
	
void Scene::drawObjects(Program *prog, int modelUniformMatrixLocation, int perspectiveMatrixLocation, int vLocation, int texCoordLocation, int vertexColorLocation, int samplerLocation) 
{
	prog->setUniformValue(perspectiveMatrixLocation, getPerspectiveMatrix(m_cx, m_cy, m_cz, m_direction, m_up, m_fovy, m_aspect, m_near, m_far));
	for (int i = 0; i<m_objects.size(); i++) 
	{
		SceneObject *obj = m_objects.at(i);
		obj->setAttributes(prog, vLocation, texCoordLocation, vertexColorLocation, modelUniformMatrixLocation, samplerLocation);
		obj->bindTexture();
		obj->bindIndexBuffer();
		obj->draw();
	}
}
