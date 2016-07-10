
#include "OctreeModel.hpp"


OctreeModel::OctreeModel(Octree* root, int precisionx, int precisiony, int precisionz) 
{
	m_precisionx = precisionx; 
	m_precisiony = precisiony; 
	m_precisionz = precisionz; 

	m_vertex_count = 0; 
	m_root = root; 
	addNode(m_root);
}

void OctreeModel::addNode(Octree* node) 
{
	if (! node->hasChilds()) 
	{
		if (node->active()) 
		{
			Vector start = node->start();
			Vector end = node->end();
			float x = 2.0*start.getX() / float(m_precisionx) - 1.0;
			float y = 2.0*start.getY() / float(m_precisiony) - 1.0;
			float z = 2.0*start.getZ() / float(m_precisionz) - 1.0;
			float endx = 2.0*end.getX() / float(m_precisionx) - 1.0;
			float endy = 2.0*end.getY() / float(m_precisiony) - 1.0;
			float endz = 2.0*end.getZ() / float(m_precisionz) - 1.0;
			float sx = endx - x; 
			float sy = endy - y; 
			float sz = endz - z; 
	
			m_vertices.push_back(x); m_vertices.push_back(y); m_vertices.push_back(z);
			m_vertices.push_back(x+sx); m_vertices.push_back(y); m_vertices.push_back(z);
			m_vertices.push_back(x+sx); m_vertices.push_back(y); m_vertices.push_back(z+sz);
			m_vertices.push_back(x); m_vertices.push_back(y); m_vertices.push_back(z+sz);
	
			m_vertices.push_back(x); m_vertices.push_back(y+sy); m_vertices.push_back(z);
			m_vertices.push_back(x+sx); m_vertices.push_back(y+sy); m_vertices.push_back(z);
			m_vertices.push_back(x+sx); m_vertices.push_back(y+sy); m_vertices.push_back(z+sz);
			m_vertices.push_back(x); m_vertices.push_back(y+sy); m_vertices.push_back(z+sz);
						
			m_indices.push_back(8*m_vertex_count + 0); m_indices.push_back(8*m_vertex_count + 1); m_indices.push_back(8*m_vertex_count + 2);
			m_indices.push_back(8*m_vertex_count + 0); m_indices.push_back(8*m_vertex_count + 3); m_indices.push_back(8*m_vertex_count + 2);
						
			m_indices.push_back(8*m_vertex_count + 0); m_indices.push_back(8*m_vertex_count + 3); m_indices.push_back(8*m_vertex_count + 4);
			m_indices.push_back(8*m_vertex_count + 3); m_indices.push_back(8*m_vertex_count + 4); m_indices.push_back(8*m_vertex_count + 7);
	
			m_indices.push_back(8*m_vertex_count + 1); m_indices.push_back(8*m_vertex_count + 2); m_indices.push_back(8*m_vertex_count + 5);
			m_indices.push_back(8*m_vertex_count + 2); m_indices.push_back(8*m_vertex_count + 5); m_indices.push_back(8*m_vertex_count + 6);
	
			m_indices.push_back(8*m_vertex_count + 0); m_indices.push_back(8*m_vertex_count + 1); m_indices.push_back(8*m_vertex_count + 5);
			m_indices.push_back(8*m_vertex_count + 0); m_indices.push_back(8*m_vertex_count + 4); m_indices.push_back(8*m_vertex_count + 5);
					
			m_indices.push_back(8*m_vertex_count + 2); m_indices.push_back(8*m_vertex_count + 3); m_indices.push_back(8*m_vertex_count + 6);
			m_indices.push_back(8*m_vertex_count + 3); m_indices.push_back(8*m_vertex_count + 6); m_indices.push_back(8*m_vertex_count + 7);

			m_indices.push_back(8*m_vertex_count + 4); m_indices.push_back(8*m_vertex_count + 5); m_indices.push_back(8*m_vertex_count + 6);
			m_indices.push_back(8*m_vertex_count + 4); m_indices.push_back(8*m_vertex_count + 6); m_indices.push_back(8*m_vertex_count + 7);
			
			// normals 
			m_normals.push_back(-1); m_normals.push_back(-1); m_normals.push_back(-1);
			m_normals.push_back(1); m_normals.push_back(-1); m_normals.push_back(-1);
			m_normals.push_back(1); m_normals.push_back(-1); m_normals.push_back(1);
			m_normals.push_back(-1); m_normals.push_back(-1); m_normals.push_back(1);
	
			m_normals.push_back(-1); m_normals.push_back(1); m_normals.push_back(-1);
			m_normals.push_back(1); m_normals.push_back(1); m_normals.push_back(-1);
			m_normals.push_back(1); m_normals.push_back(1); m_normals.push_back(1);
			m_normals.push_back(-1); m_normals.push_back(1); m_normals.push_back(1);

			m_vertex_count++;
			// dummy colors lol
			for (int i = 0; i<8; i++) {
				m_colors.push_back(1.0); 
				m_colors.push_back(0.0);
				m_colors.push_back(0.0);
				m_colors.push_back(1.0);
	
				m_textures.push_back(0.0);
				m_textures.push_back(1.0);
			}
		}
	}
	else 
	{
		for (int i = 0; i<8; i++) 
		{
			addNode(node->getChild(i));
		}
	}
}

std::vector<float> OctreeModel::genVertices() 
{
	return m_vertices;
}

std::vector<int> OctreeModel::genIndices() 
{
	return m_indices;
}

std::vector<float> OctreeModel::genVertexColors() 
{
	return m_colors; 
}

std::vector<float> OctreeModel::genTextureCoordinates() 
{
	return m_textures;
}

std::vector<float> OctreeModel::genNormals() 
{
	return m_normals;
}
