

#include "FilledSurfaceModel.hpp"

using namespace std;

#define EDGE_RIGHT x == 1.0 || function_top(x+dx,z) == function_bottom(x+dx,z)
#define EDGE_LEFT x == -1.0 || function_top(x-dx,z) == function_bottom(x-dx,z)

#define EDGE_UP z == 1.0 || function_top(x,z+dz) == function_bottom(x,z+dz)
#define EDGE_DOWN z == -1.0 || function_top(x,z-dz) == function_bottom(x,z-dz)

FilledSurfaceModel::FilledSurfaceModel(int precision) 
{
	m_precision = precision;
}

std::vector<float> FilledSurfaceModel::genVertices() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertices; 
	int level;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			if (function_top(x,z) - function_bottom(x,z) != 0
				&& function_top(x+dx,z) - function_bottom(x+dx,z) != 0
				&& function_top(x,z+dz) - function_bottom(x,z+dz) != 0
				&& function_top(x+dx,z+dz) - function_bottom(x+dx,z+dz) != 0
			)
			{
				// top
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
	}
	float x,z;
	for (x = -1.0; x<= 1.0; x += dx) 
	{
		for (z = -1.0; z<1.0; z += dz) 
		{
			if (EDGE_RIGHT || EDGE_LEFT) 
			{
				vertices.push_back(x);
				vertices.push_back(function_top(x,z)); 
				vertices.push_back(z);
				
				vertices.push_back(x);
				vertices.push_back(function_top(x,z+dz)); 
				vertices.push_back(z+dz);
				
				vertices.push_back(x);
				vertices.push_back(function_bottom(x,z)); 
				vertices.push_back(z);
				
				vertices.push_back(x);
				vertices.push_back(function_bottom(x,z+dz)); 
				vertices.push_back(z+dz);
			}
		}
	}
	for (x = -1.0; x < 1.0; x += dx) 
	{
		for (z = -1.0; z<=1.0; z += dz) 
		{
			if (EDGE_UP || EDGE_DOWN) 
			{
				vertices.push_back(x);
				vertices.push_back(function_top(x,z)); 
				vertices.push_back(z);
				
				vertices.push_back(x+dx);
				vertices.push_back(function_top(x+dx,z)); 
				vertices.push_back(z);
				
				vertices.push_back(x);
				vertices.push_back(function_bottom(x,z)); 
				vertices.push_back(z);
				
				vertices.push_back(x+dx);
				vertices.push_back(function_bottom(x+dx,z)); 
				vertices.push_back(z);
			}
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
	int level;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			if (function_top(x,z) - function_bottom(x,z) != 0
				&& function_top(x+dx,z) - function_bottom(x+dx,z) != 0
				&& function_top(x,z+dz) - function_bottom(x,z+dz) != 0
				&& function_top(x+dx,z+dz) - function_bottom(x+dx,z+dz) != 0
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
	int points = index;
	index = 0;

	float x,z;
	for (x = -1.0; x<= 1.0; x += dx) 
	{
		for (z = -1.0; z<1.0; z += dz) 
		{
			if (EDGE_RIGHT || EDGE_LEFT) 
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
			if (EDGE_UP || EDGE_DOWN) 
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
	return indices;
	
}

std::vector<float> FilledSurfaceModel::genVertexColors() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> vertexColors; 
	int level;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			if (function_top(x,z) - function_bottom(x,z) != 0
				&& function_top(x+dx,z) - function_bottom(x+dx,z) != 0
				&& function_top(x,z+dz) - function_bottom(x,z+dz) != 0
				&& function_top(x+dx,z+dz) - function_bottom(x+dx,z+dz) != 0
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
	float x,z;
	for (x = -1.0; x<= 1.0; x += dx) 
	{
		for (z = -1.0; z<1.0; z += dz) 
		{
			if (EDGE_RIGHT || EDGE_LEFT) 
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
			if (EDGE_UP || EDGE_DOWN) 
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
	return vertexColors;
	
}

std::vector<float> FilledSurfaceModel::genTextureCoordinates() 
{
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> coords; 
	int level;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			if (function_top(x,z) - function_bottom(x,z) != 0
				&& function_top(x+dx,z) - function_bottom(x+dx,z) != 0
				&& function_top(x,z+dz) - function_bottom(x,z+dz) != 0
				&& function_top(x+dx,z+dz) - function_bottom(x+dx,z+dz) != 0
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
	float x,z;
	for (x = -1.0; x<= 1.0; x += dx) 
	{
		for (z = -1.0; z<1.0; z += dz) 
		{
			if (EDGE_RIGHT || EDGE_LEFT) 
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
			if (EDGE_UP || EDGE_DOWN) 
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
	return coords;
}

std::vector<float> FilledSurfaceModel::genNormals() 
{
	
	float dz = 2.0 / m_precision; 
	float dx = dz = 2.0 / m_precision;
	vector<float> normals; 
	int level;
	for (float x = -1.0; x< 1.0; x += dx) 
	{
		for (float z = -1.0; z<1.0; z += dz) 
		{
			if (function_top(x,z) - function_bottom(x,z) != 0
				&& function_top(x+dx,z) - function_bottom(x+dx,z) != 0
				&& function_top(x,z+dz) - function_bottom(x,z+dz) != 0
				&& function_top(x+dx,z+dz) - function_bottom(x+dx,z+dz) != 0
			)
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
	}
	float x,z;
	for (x = -1.0; x<= 1.0; x += dx) 
	{
		for (z = -1.0; z<1.0; z += dz) 
		{
			if (EDGE_RIGHT || EDGE_LEFT) 
			{
				Vector normal(0.0,0.0,0.0);
				if (EDGE_RIGHT) normal = Vector(1.0,0.0,0.0);
				if (EDGE_LEFT) normal = Vector(-1.0,0.0,0.0);
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
			if (EDGE_UP || EDGE_DOWN) 
			{
				Vector normal(0.0,0.0,0.0);
				if (EDGE_UP) normal = Vector(0.0,0.0,1.0);
				if (EDGE_DOWN) normal = Vector(0.0,0.0,-1.0);
				for (int i = 0; i<4; i++) {
					normals.push_back(normal.getX());
					normals.push_back(normal.getY());
					normals.push_back(normal.getZ());
				}
			}
		}
	}
	return normals;
}
