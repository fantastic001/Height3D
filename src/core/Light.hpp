
#ifndef HEIGHT3D_LIGHT_HPP
#define HEIGHT3D_LIGHT_HPP

#include "Vector.hpp"
#include "Color.hpp"

/// Represents light which can be added to Scene object
class Light 
{

	float m_x, m_y, m_z; 
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;
public:
	Light(float x, float y, float z,
		Color ambient, Color diffuse, Color specular
		);
	
	Vector getPosition();

	Color getAmbient();
	Color getDiffuse();
	Color getSpecular();
};

#endif // HEIGHT3D_LIGHT_HPP
