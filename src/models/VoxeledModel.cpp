
#include "VoxeledModel.hpp"

VoxeledModel::VoxeledModel(Array3D<bool> &array) 
{
	m_array = array; 
}

std::vector<float> VoxeledModel::genVertices() 
{
	std::vector<float> v; 

	// compute steps 
	float sx,sy,sz; 
	sx = 2.0 / m_array.getSizeX(); 
	sy = 2.0 / m_array.getSizeY();
	sz = 2.0 / m_array.getSizeZ();
	for (int i = 0; i<m_array.getSizeX(); i++) 
	{
		for (int j = 0; j<m_array.getSizeY(); j++) 
		{
			for (int k = 0; k<m_array.getSizeZ(); k++) 
			{
				if (m_array(i,j,k)) 
				{
					float x,y,z; 
					x = -1 + sx*i; 
					y = -1 + sy*j; 
					z = -1 + sz*k;
					// we are adding 8 vertices 

					v.push_back(x); v.push_back(y); v.push_back(z);
					v.push_back(x+sx); v.push_back(y); v.push_back(z);
					v.push_back(x+sx); v.push_back(y); v.push_back(z+sz);
					v.push_back(x); v.push_back(y); v.push_back(z+sz);

					v.push_back(x); v.push_back(y+sy); v.push_back(z);
					v.push_back(x+sx); v.push_back(y+sy); v.push_back(z);
					v.push_back(x+sx); v.push_back(y+sy); v.push_back(z+sz);
					v.push_back(x); v.push_back(y+sy); v.push_back(z+sz);
				}
			}
		}
	}
	return v; 
}
	
std::vector<int> VoxeledModel::genIndices() 
{
	std::vector<int> v; 
	int start = 0;
	for (int i = 0; i<m_array.getSizeX(); i++) 
	{
		for (int j = 0; j<m_array.getSizeY(); j++) 
		{
			for (int k = 0; k<m_array.getSizeZ(); k++) 
			{
				if (m_array(i,j,k)) 
				{
					v.push_back(8*start + 0); v.push_back(8*start + 1); v.push_back(8*start + 2);
					v.push_back(8*start + 0); v.push_back(8*start + 3); v.push_back(8*start + 2);
					
					v.push_back(8*start + 0); v.push_back(8*start + 3); v.push_back(8*start + 4);
					v.push_back(8*start + 3); v.push_back(8*start + 4); v.push_back(8*start + 7);

					v.push_back(8*start + 1); v.push_back(8*start + 2); v.push_back(8*start + 5);
					v.push_back(8*start + 2); v.push_back(8*start + 5); v.push_back(8*start + 6);

					v.push_back(8*start + 0); v.push_back(8*start + 1); v.push_back(8*start + 5);
					v.push_back(8*start + 0); v.push_back(8*start + 4); v.push_back(8*start + 5);
					
					v.push_back(8*start + 2); v.push_back(8*start + 3); v.push_back(8*start + 6);
					v.push_back(8*start + 3); v.push_back(8*start + 6); v.push_back(8*start + 7);

					v.push_back(8*start + 4); v.push_back(8*start + 5); v.push_back(8*start + 6);
					v.push_back(8*start + 4); v.push_back(8*start + 6); v.push_back(8*start + 7);

					start++;
				}
			}
		}
	}
	return v; 

}
	
std::vector<float> VoxeledModel::genVertexColors() 
{
	std::vector<float> v; 

	for (int i = 0; i<m_array.getSizeX(); i++) 
	{
		for (int j = 0; j<m_array.getSizeY(); j++) 
		{
			for (int k = 0; k<m_array.getSizeZ(); k++) 
			{
				if (m_array(i,j,k)) 
				{
					Color c = voxelColor(i,j,k);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
					v.push_back(c.red); v.push_back(c.green); v.push_back(c.blue); v.push_back(c.alpha);
				}
			}
		}
	}
	return v; 

}
	
std::vector<float> VoxeledModel::genTextureCoordinates() 
{

	std::vector<float> v; 

	for (int i = 0; i<m_array.getSizeX(); i++) 
	{
		for (int j = 0; j<m_array.getSizeY(); j++) 
		{
			for (int k = 0; k<m_array.getSizeZ(); k++) 
			{
				if (m_array(i,j,k)) 
				{
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
					v.push_back(1.0); v.push_back(0);
				}
			}
		}
	}
	return v; 
}

std::vector<float> VoxeledModel::genNormals() 
{

	std::vector<float> v; 

	for (int i = 0; i<m_array.getSizeX(); i++) 
	{
		for (int j = 0; j<m_array.getSizeY(); j++) 
		{
			for (int k = 0; k<m_array.getSizeZ(); k++) 
			{
				if (m_array(i,j,k)) 
				{
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
					v.push_back(1.0); v.push_back(0); v.push_back(0);
				}
			}
		}
	}
	return v; 

}
