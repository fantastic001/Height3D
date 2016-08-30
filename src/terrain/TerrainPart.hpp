
#ifndef HEIGHT3D_TERRAIN_TERRAIN_PART_HPP
#define HEIGHT3D_TERRAIN_TERRAIN_PART_HPP

#include <core/DynamicSceneObject.hpp>
#include <structures/heightfield/LayeredHeightfield.hpp>
#include <structures/heightfield/LayeredHeightfieldModel.hpp>

#include <string>

class TerrainPart : public DynamicSceneObject 
{
	std::string m_path; 
	float m_x, m_z;
	float m_height; 
	Material m_material;
	bool m_visible;
	float m_threshold;
	float m_size; 

	LayeredHeightfieldModel* m_model;
	SceneObject* m_object; 
	Texture* m_texture;
public:
	TerrainPart(const char* path, float x, float z, float size, float height, Material material, float threshold);
	
	SceneObject* getObject(Vector camera_position);
};

#endif // HEIGHT3D_TERRAIN_TERRAIN_PART_HPP
