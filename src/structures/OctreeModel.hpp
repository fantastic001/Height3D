
#ifndef HEIGHT3D_STRUCTURES_OCTREE_MODEL_HPP
#define HEIGHT3D_STRUCTURES_OCTREE_MODEL_HPP

#include <core/AbstractModel.hpp>

#include "Octree.hpp"


class OctreeModel : public AbstractModel 
{
	int m_precisionx, m_precisiony, m_precisionz;
	void addNode(Octree* node);

	Octree* m_root;
	int m_vertex_count;
	std::vector<float> m_vertices; 
	std::vector<int> m_indices; 
	std::vector<float> m_colors;
	std::vector<float> m_textures;

public:
	OctreeModel(Octree* root, int precisionx, int precisiony, int precisionz);

protected:

	std::vector<float> genVertices(); 
	
	std::vector<int> genIndices(); 
	
	std::vector<float> genVertexColors();
	
	std::vector<float> genTextureCoordinates();

	std::vector<float> genNormals();
};

#endif // HEIGHT3D_STRUCTURES_OCTREE_MODEL_HPP
