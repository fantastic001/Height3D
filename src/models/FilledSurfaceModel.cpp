
#include "FilledSurfaceModel.hpp"



using namespace std;

FilledSurfaceModel::FilledSurfaceModel(int precision) 
{
	m_precision = precision; 
}

std::vector<float> FilledSurfaceModel::genVertices() 
{	
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertices; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			// up 
			vertices.push_back(x);
			vertices.push_back(function_top(x,z));
			vertices.push_back(z);
			
			vertices.push_back(x+dx);
			vertices.push_back(function_top(x+dx,z));
			vertices.push_back(z);
			
			vertices.push_back(x);
			vertices.push_back(function_top(x,z+dz));
			vertices.push_back(z+dz);
			
			vertices.push_back(x+dx);
			vertices.push_back(function_top(x+dx,z+dz));
			vertices.push_back(z+dz);
			
			// down
			vertices.push_back(x);
			vertices.push_back(function_bottom(x,z));
			vertices.push_back(z);
			
			vertices.push_back(x+dx);
			vertices.push_back(function_bottom(x+dx,z));
			vertices.push_back(z);
			
			vertices.push_back(x);
			vertices.push_back(function_bottom(x,z+dz));
			vertices.push_back(z+dz);
			
			vertices.push_back(x+dx);
			vertices.push_back(function_bottom(x+dx,z+dz));
			vertices.push_back(z+dz);
		}
	}
	return vertices;
}

std::vector<int> FilledSurfaceModel::genIndices() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<int> indices; 
	int index = 0;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
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

			// sides 
			indices.push_back(8*index + 0);
			indices.push_back(8*index + 1);
			indices.push_back(8*index + 4);

			indices.push_back(8*index + 1);
			indices.push_back(8*index + 4);
			indices.push_back(8*index + 5);
			
			indices.push_back(8*index + 0);
			indices.push_back(8*index + 2);
			indices.push_back(8*index + 4);

			indices.push_back(8*index + 2);
			indices.push_back(8*index + 4);
			indices.push_back(8*index + 6);
			
			indices.push_back(8*index + 1);
			indices.push_back(8*index + 3);
			indices.push_back(8*index + 5);

			indices.push_back(8*index + 3);
			indices.push_back(8*index + 5);
			indices.push_back(8*index + 7);
			
			indices.push_back(8*index + 2);
			indices.push_back(8*index + 3);
			indices.push_back(8*index + 6);

			indices.push_back(8*index + 3);
			indices.push_back(8*index + 6);
			indices.push_back(8*index + 7);

			index++;

		}
	}
	return indices;
}

std::vector<float> FilledSurfaceModel::genVertexColors() 
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

std::vector<float> FilledSurfaceModel::genTextureCoordinates() 
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

std::vector<float> FilledSurfaceModel::genNormals() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> normals; 
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			int i;
			// top
			Vector v1(0, function_top(x,z+dz) - function_top(x,z), dz);
			Vector v2(dx, function_top(x+dx,z) - function_top(x,z), 0);
			Vector normal = v2.cross(v1);
			normal = Vector(-normal.getX(), -normal.getY(), -normal.getZ());
			
			// We have 4 vertices 
			for (i = 0; i<4; i++) {
				normals.push_back(normal.getX());
				normals.push_back(normal.getY());
				normals.push_back(normal.getZ());
			}
			
			// bottom
			Vector v3(0, function_bottom(x,z+dz) - function_bottom(x,z), dz);
			Vector v4(dx, function_bottom(x+dx,z) - function_bottom(x,z), 0);
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
	return normals;
}
