
#ifndef HEIGHT3D_SCENE_HPP
#define HEIGHT3D_SCENE_HPP

#include <vector>

#include "SceneObject.hpp"
#include "AbstractModel.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Program.hpp"

class Scene 
{
	// scene parameters 
	std::vector<SceneObject*> m_objects; 
	float m_fovy, m_aspect, m_near, m_far;
	
	// camera parameters
	float m_cx, m_cy, m_cz;
	Vector m_direction;
	Vector m_up;

public:
	Scene();
	~Scene();

	SceneObject* addObject(SceneObject* object);
	// addLight(AbstractLight, float x, float y, float z);
	void setCamera(float x, float y, float z, Vector direction, Vector up);
	
	/*
	Sets perspective parameters

	NOTE: fovy is given in radians
	*/
	void setPerspective(float fovy, float aspect, float near, float far);
	

	/*
	Return matrix to project scene object into camera space with perspective projection

	NOTE: fovy is given in radians 
	NoTE 2: aspect is your aspect ratio
	*/
	static Matrix getPerspectiveMatrix(float x, float y, float z, Vector direction, Vector up, float fovy, float aspect, float near, float far);
	

	void drawObjects(Program *prog, int modelUniformMatrixLocation, int perspectiveMatrixLocation, int vLocation, int texCoordLocation, int vertexColorLocation, int samplerLocatio);
};

#endif // HEIGHT3D_SCENE_HPP
