#ifndef HEIGHT3D_SCENE_OBJECT_HPP
#define HEIGHT3D_SCENE_OBJECT_HPP

#include "AbstractModel.hpp"
#include "Vector.hpp"
#include "Program.hpp"
#include "Buffer.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Color.hpp"

class SceneObject 
{
	bool m_sent;
	bool m_cacheable;

	float m_x,m_y,m_z; 
	float m_alpha, m_phi; 
	float m_a,m_b,m_c; 
	AbstractModel *m_model;
	Texture *m_texture; 
	Buffer* vBuffer; 
	Buffer* tBuffer;
	Buffer* cBuffer;
	Buffer* iBuffer;
	Buffer* nBuffer;

	Material m_material;

public:
	SceneObject(AbstractModel *_model, Texture *_texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c, bool cacheable = true);
	SceneObject(AbstractModel *_model, Texture *_texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c, Material material, bool cacheable = true);

	/*!
	Texture and AbstractModel won't be deleted after SceneObject is deleted
	*/
	~SceneObject();
	
	void move(Vector t);
	void rotate(float _alpha, float _phi);

	Vector getPosition();

	/// Sets all attributes on given locations on specified program
	void setAttributes(Program* prog, int vLocation, int texCoordLocation, int vertexColorLocation, int modelLocation, int samplerLocation, int normalLocation = -1);

	/// Binds texture
	void bindTexture();

	/// binds index buffer
	void bindIndexBuffer();
	
	Color getAmbientProduct(Light *light);
	Color getDiffuseProduct(Light *light);
	Color getSpecularProduct(Light *light);

	/*!
	Returns currently used material 
	*/
	Material getMaterial();
	
	/// Draws object on the scene 
	void draw();
};

#endif // HEIGHT3D_SCENE_OBJECT_HPP
