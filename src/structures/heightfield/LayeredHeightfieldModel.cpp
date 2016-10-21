

#include "LayeredHeightfieldModel.hpp"

using namespace std;

#define EDGE_RIGHT(h) x == 1.0 || h->getTop(level, x+dx,z) == h->getBottom(level, x+dx,z)
#define EDGE_LEFT(h) x == -1.0 || h->getTop(level, x-dx,z) == h->getBottom(level, x-dx,z)

#define EDGE_UP(h) z == 1.0 || h->getTop(level, x,z+dz) == h->getBottom(level, x,z+dz)
#define EDGE_DOWN(h) z == -1.0 || h->getTop(level, x,z-dz) == h->getBottom(level, x,z-dz)

LayeredHeightfieldModel::LayeredHeightfieldModel(LayeredHeightfield *heightfield) 
{
	m_heightfield = heightfield;
	m_precision = m_heightfield->getPrecision();
}

LayeredHeightfield* LayeredHeightfieldModel::getField() 
{
	return m_heightfield;
}

std::vector<float> LayeredHeightfieldModel::genVertices() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertices; 
	int level;
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		for (float x = -1.0; x< 1.0; x += dx) 
		{
			for (float z = -1.0; z<1.0; z += dz) 
			{
				if (m_heightfield->getTop(level,x,z) - m_heightfield->getBottom(level,x,z) != 0
					&& m_heightfield->getTop(level,x+dx,z) - m_heightfield->getBottom(level,x+dx,z) != 0
					&& m_heightfield->getTop(level,x,z+dz) - m_heightfield->getBottom(level,x,z+dz) != 0
					&& m_heightfield->getTop(level,x+dx,z+dz) - m_heightfield->getBottom(level,x+dx,z+dz) != 0
				)
				{
					// top
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getTop(level, x,z));
					vertices.push_back(z);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getTop(level, x+dx,z));
					vertices.push_back(z);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getTop(level, x,z+dz));
					vertices.push_back(z+dz);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getTop(level, x+dx,z+dz));
					vertices.push_back(z+dz);
					
					// down 
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getBottom(level, x,z));
					vertices.push_back(z);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getBottom(level, x+dx,z));
					vertices.push_back(z);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getBottom(level, x,z+dz));
					vertices.push_back(z+dz);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getBottom(level, x+dx,z+dz));
					vertices.push_back(z+dz);
				}
			}
		}
	}
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getTop(level,x,z)); 
					vertices.push_back(z);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getTop(level,x,z+dz)); 
					vertices.push_back(z+dz);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getBottom(level,x,z)); 
					vertices.push_back(z);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getBottom(level,x,z+dz)); 
					vertices.push_back(z+dz);
				}
			}
		}
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getTop(level,x,z)); 
					vertices.push_back(z);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getTop(level,x+dx,z)); 
					vertices.push_back(z);
					
					vertices.push_back(x);
					vertices.push_back(m_heightfield->getBottom(level,x,z)); 
					vertices.push_back(z);
					
					vertices.push_back(x+dx);
					vertices.push_back(m_heightfield->getBottom(level,x+dx,z)); 
					vertices.push_back(z);
				}
			}
		}
	}
	return vertices;
	
}

std::vector<int> LayeredHeightfieldModel::genIndices() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<int> indices; 
	int index = 0;
	int level;
	for (level = 0; level<m_heightfield->levelCount();  level++) 
	{
		for (float x = -1.0; x< 1.0; x += dx) 
		{
			for (float z = -1.0; z<1.0; z += dz) 
			{
				if (m_heightfield->getTop(level,x,z) - m_heightfield->getBottom(level,x,z) != 0
					&& m_heightfield->getTop(level,x+dx,z) - m_heightfield->getBottom(level,x+dx,z) != 0
					&& m_heightfield->getTop(level,x,z+dz) - m_heightfield->getBottom(level,x,z+dz) != 0
					&& m_heightfield->getTop(level,x+dx,z+dz) - m_heightfield->getBottom(level,x+dx,z+dz) != 0
				)
				{
					// top
					indices.push_back(8*index + 0);
					indices.push_back(8*index + 1);
					indices.push_back(8*index + 2);
			
					indices.push_back(8*index + 1);
					indices.push_back(8*index + 2);
					indices.push_back(8*index + 3);
					
					// bottom
					indices.push_back(8*index + 4);
					indices.push_back(8*index + 5);
					indices.push_back(8*index + 6);
		
					indices.push_back(8*index + 5);
					indices.push_back(8*index + 6);
					indices.push_back(8*index + 7);
		
		
					index++;
				}
			}
		}
	}
	int points = index;
	index = 0;

	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{
					indices.push_back(8*points + 4*index + 0);
					indices.push_back(8*points + 4*index + 1);
					indices.push_back(8*points + 4*index + 2);
					indices.push_back(8*points + 4*index + 1);
					indices.push_back(8*points + 4*index + 2);
					indices.push_back(8*points + 4*index + 3);
					
					index++;
				}
			}
		}
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					indices.push_back(8*points + 4*index + 0);
					indices.push_back(8*points + 4*index + 1);
					indices.push_back(8*points + 4*index + 2);
					indices.push_back(8*points + 4*index + 1);
					indices.push_back(8*points + 4*index + 2);
					indices.push_back(8*points + 4*index + 3);
					index++;
				}
			}
		}
	}
	return indices;
	
}

std::vector<float> LayeredHeightfieldModel::genVertexColors() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertexColors; 
	int level;
	for (level = 0; level<m_heightfield->levelCount(); level++) 
	{
		for (float x = -1.0; x< 1.0; x += dx) 
		{
			for (float z = -1.0; z<1.0; z += dz) 
			{
				if (m_heightfield->getTop(level,x,z) - m_heightfield->getBottom(level,x,z) != 0
					&& m_heightfield->getTop(level,x+dx,z) - m_heightfield->getBottom(level,x+dx,z) != 0
					&& m_heightfield->getTop(level,x,z+dz) - m_heightfield->getBottom(level,x,z+dz) != 0
					&& m_heightfield->getTop(level,x+dx,z+dz) - m_heightfield->getBottom(level,x+dx,z+dz) != 0
				)
				{
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
				}
			}
		}
	}
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{

					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
				}
			}
		}
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
		
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
					vertexColors.push_back(1.0);
				}
			}
		}
	}
	return vertexColors;
	
}

std::vector<float> LayeredHeightfieldModel::genTextureCoordinates() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> coords; 
	int level;
	for (level = 0; level<m_heightfield->levelCount(); level++)
	{
		for (float x = -1.0; x< 1.0; x += dx) 
		{
			for (float z = -1.0; z<1.0; z += dz) 
			{
				if (m_heightfield->getTop(level,x,z) - m_heightfield->getBottom(level,x,z) != 0
					&& m_heightfield->getTop(level,x+dx,z) - m_heightfield->getBottom(level,x+dx,z) != 0
					&& m_heightfield->getTop(level,x,z+dz) - m_heightfield->getBottom(level,x,z+dz) != 0
					&& m_heightfield->getTop(level,x+dx,z+dz) - m_heightfield->getBottom(level,x+dx,z+dz) != 0
				)
				{
					float u,v; 
					u = 0.5*x + 0.5;
					v = 0.5*z + 0.5;
					coords.push_back(u);
					coords.push_back(v);
					
					coords.push_back(u + 0.5*dx);
					coords.push_back(v);
					
					coords.push_back(u);
					coords.push_back(v + 0.5*dz);
					
					coords.push_back(u + 0.5*dx);
					coords.push_back(v + 0.5*dz);
					
					coords.push_back(u);
					coords.push_back(v);
					
					coords.push_back(u + 0.5*dx);
					coords.push_back(v);
					
					coords.push_back(u);
					coords.push_back(v + 0.5*dz);
					
					coords.push_back(u + 0.5*dx);
					coords.push_back(v + 0.5*dz);
				}
			}
		}
	}
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{
					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);
				}
			}
		}
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);

					coords.push_back(0.0);
					coords.push_back(0.0);
				}
			}
		}
	}
	return coords;
}

std::vector<float> LayeredHeightfieldModel::genNormals() 
{
	
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> normals; 
	int level;
	for (level = 0; level<m_heightfield->levelCount(); level++) 
	{
		for (float x = -1.0; x< 1.0; x += dx) 
		{
			for (float z = -1.0; z<1.0; z += dz) 
			{
				if (m_heightfield->getTop(level,x,z) - m_heightfield->getBottom(level,x,z) != 0
					&& m_heightfield->getTop(level,x+dx,z) - m_heightfield->getBottom(level,x+dx,z) != 0
					&& m_heightfield->getTop(level,x,z+dz) - m_heightfield->getBottom(level,x,z+dz) != 0
					&& m_heightfield->getTop(level,x+dx,z+dz) - m_heightfield->getBottom(level,x+dx,z+dz) != 0
				)
				{
					int i;
					// top
					Vector v1(0, m_heightfield->getTop(level, x,z+dz) - m_heightfield->getTop(level, x,z), dz);
					Vector v2(dx, m_heightfield->getTop(level, x+dx,z) - m_heightfield->getTop(level, x,z), 0);
					Vector normal = v2.cross(v1);
					normal = Vector(-normal.getX(), -normal.getY(), -normal.getZ());
					
					// We have 4 vertices 
					for (i = 0; i<4; i++) {
						normals.push_back(normal.getX());
						normals.push_back(normal.getY());
						normals.push_back(normal.getZ());
					}
					
					// bottom
					Vector v3(0, m_heightfield->getBottom(level, x,z+dz) - m_heightfield->getBottom(level, x,z), dz);
					Vector v4(dx, m_heightfield->getBottom(level, x+dx,z) - m_heightfield->getBottom(level, x,z), 0);
					Vector normal2 = v4.cross(v3);
					normal2 = Vector(normal2.getX(), normal2.getY(), normal2.getZ());
					
					// We have 4 vertices 
					for (i = 0; i<4; i++) {
						normals.push_back(normal2.getX());
						normals.push_back(normal2.getY());
						normals.push_back(normal2.getZ());
					}
				}
			}
		}
	}
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{
					Vector normal(0.0,0.0,0.0);
					if (EDGE_RIGHT(m_heightfield)) normal = Vector(1.0,0.0,0.0);
					if (EDGE_LEFT(m_heightfield)) normal = Vector(-1.0,0.0,0.0);
					for (int i = 0; i<4 ;i++) {
						normals.push_back(normal.getX());
						normals.push_back(normal.getY());
						normals.push_back(normal.getZ());
					}
				}
			}
		}
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					Vector normal(0.0,0.0,0.0);
					if (EDGE_UP(m_heightfield)) normal = Vector(0.0,0.0,1.0);
					if (EDGE_DOWN(m_heightfield)) normal = Vector(0.0,0.0,-1.0);
					for (int i = 0; i<4; i++) {
						normals.push_back(normal.getX());
						normals.push_back(normal.getY());
						normals.push_back(normal.getZ());
					}
				}
			}
		}
	}
	return normals;
}


int LayeredHeightfieldModel::countLeftRightEdges() 
{
	int c = 0
	for (level = 0; level<m_heightfield->levelCount(); level++) {
		float x,z;
		for (x = -1.0; x<= 1.0; x += dx) 
		{
			for (z = -1.0; z<1.0; z += dz) 
			{
				if (EDGE_RIGHT(m_heightfield) || EDGE_LEFT(m_heightfield)) 
				{
					c++;
				}
			}
		}
	}
	return c;
}
int LayeredHeightfieldModel::countForwardBackwardEdges() 
{
	
	int c = 0;
	for (int level = 0; level<m_heightfield->levelCount(); level++) {
		for (x = -1.0; x < 1.0; x += dx) 
		{
			for (z = -1.0; z<=1.0; z += dz) 
			{
				if (EDGE_UP(m_heightfield) || EDGE_DOWN(m_heightfield)) 
				{
					Vector normal(0.0,0.0,0.0);
					if (EDGE_UP(m_heightfield)) normal = Vector(0.0,0.0,1.0);
					if (EDGE_DOWN(m_heightfield)) normal = Vector(0.0,0.0,-1.0);
					for (int i = 0; i<4; i++) {
						normals.push_back(normal.getX());
						normals.push_back(normal.getY());
						normals.push_back(normal.getZ());
					}
				}
			}
		}
	}
	return c; 
}
