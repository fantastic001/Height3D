
#include "Light.hpp"


Light::Light(float x, float y, float z,
	Color ambient, Color diffuse, Color specular
) 
{
	m_x = x; 
	m_y = y; 
	m_z = z;

	m_ambient = ambient; 
	m_diffuse = diffuse; 
	m_specular = specular;
} 

Vector Light::getPosition() 
{
	return Vector(m_x, m_y, m_z, 1.0);
}
