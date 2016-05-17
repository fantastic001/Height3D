
#include "SurfaceModel.hpp"



using namespace std;

SurfaceModel::SurfaceModel(int precision) 
{
	m_precision = precision; 
}

std::vector<float> SurfaceModel::genVertices() 
{	
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertices; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			vertices.push_back(x);
			vertices.push_back(function(x,z));
			vertices.push_back(z);
			
			vertices.push_back(x+dx);
			vertices.push_back(function(x+dx,z));
			vertices.push_back(z);
			
			vertices.push_back(x);
			vertices.push_back(function(x,z+dz));
			vertices.push_back(z+dz);
			
			vertices.push_back(x+dx);
			vertices.push_back(function(x+dx,z+dz));
			vertices.push_back(z+dz);
		}
	}
	return vertices;
}

std::vector<int> SurfaceModel::genIndices() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<int> indices; 
	int index = 0;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			indices.push_back(4*index + 0);
			indices.push_back(4*index + 1);
			indices.push_back(4*index + 2);

			indices.push_back(4*index + 1);
			indices.push_back(4*index + 2);
			indices.push_back(4*index + 3);

			index++;

		}
	}
	return indices;
}

std::vector<float> SurfaceModel::genVertexColors() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertexColors; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
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
	return vertexColors;
}

std::vector<float> SurfaceModel::genTextureCoordinates() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> coords; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
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
		}
	}
	return coords;

}

std::vector<float> SurfaceModel::genNormals() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> normals; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			Vector v1(0, function(x,z+dz) - function(x,z), dz);
			Vector v2(dx, function(x+dx,z) - function(x,z), 0);
			Vector normal = v2.cross(v1);
			normal = Vector(-normal.getX(), -normal.getY(), -normal.getZ());
			
			// We have 4 vertices 
			for (int i = 0; i<4; i++) {
				normals.push_back(normal.getX());
				normals.push_back(normal.getY());
				normals.push_back(normal.getZ());
			}
		}
	}
	return normals;
}
