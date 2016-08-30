
#include "TerrainPart.hpp"

#include <fstream>
#include <cmath>

using namespace std; 

TerrainPart::TerrainPart(const char* path, float x, float z, float size, float height, Material material, float threshold)
{
	m_path = string(path);
	m_x = x; 
	m_z = z;
	m_height = height; 
	m_material = material;
	m_visible = false; 
	m_threshold = threshold; 
	m_size = size;

	m_texture = new Texture(GL_TEXTURE_2D, 1, 1);
	m_model = NULL;
	m_object = NULL;
}
	
SceneObject* TerrainPart::getObject(Vector camera_position) 
{
	Vector distance = Vector(m_x-camera_position.getX(),m_z-camera_position.getZ(),0, 0);
	if (sqrt(distance.dot(distance)) <= m_threshold) 
	{
		if (m_visible) 
		{
			return m_object;
		}
		else 
		{
			m_visible = true;
			if (m_model != NULL && m_object != NULL) 
			{
				
				delete m_object;
				delete m_model->getField();
				delete m_model;
			}
			m_model = new LayeredHeightfieldModel(LayeredHeightfield::readFromFile(m_path.c_str()));
			m_object = new SceneObject(
				m_model, 
				m_texture, 
				m_x, 0, m_z, 
				0.0, 0.0, 
				m_size, m_height, m_size, 
				m_material
			);
		}
		return m_object;
	}
	else 
	{
		if (m_visible) 
		{
			m_visible = false;
			if (m_model != NULL && m_object != NULL) 
			{
				
				delete m_object;
				delete m_model->getField();
				delete m_model;
				m_object = NULL;
				m_model = NULL;
			}
			return NULL;

		}
		else 
		{
			return NULL;
		}

	}
}
