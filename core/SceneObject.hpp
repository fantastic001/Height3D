#ifndef HEIGHT3D_SCENE_OBJECT_HPP
#define HEIGHT3D_SCENE_OBJECT_HPP

#include "AbstractModel.hpp"
#include "Vector.hpp"
#include "Program.hpp"

class SceneObject 
{
	float m_x,m_y,m_z; 
	float m_alpha, m_phi; 
	float m_a,m_b,m_c; 
	AbstractModel m_model;
	Texture m_texture; 

public:
	SceneObject(AbstractModel _model, Texture _texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c);
	~SceneObject();
	
	void move(Vector t);
	void rotate(float _alpha, float _phi);

	Vector getPosition();
	void setAttributes(Program* prog, int vLocation, int texCoordLocation, int modelLocation);
	void bindTexture();

	void draw();
};

#endif // HEIGHT3D_SCENE_OBJECT_HPP
