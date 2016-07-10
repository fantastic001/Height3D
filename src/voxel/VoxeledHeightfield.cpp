
#include "VoxeledHeightfield.hpp"
#include <structures/octree/Array3DOctreeAdapter.hpp>

Array3D<bool> VoxeledHeightfield::generateArray(int precision) 
{
	m_precision = precision; 
	Array3D<bool> a(precision, precision, precision);
	for (int i = 0; i<precision; i++) 
	{
		for (int j = 0; j<precision; j++) 
		{
			for (int k = 0; k<precision; k++) 
			{
				a(i,j,k) = isActive(i,j,k);
			}
		}
	}
	return a;
}

Octree* VoxeledHeightfield::generateOctree(int precision) 
{
	m_precision = precision;
	generate(precision, precision, precision, true);
	return getRoot();
}

bool VoxeledHeightfield::isActive(int i, int j, int k) 
{
	float f = function(2*i / float(m_precision) - 1.0, 2*k / float(m_precision) - 1.0);
	int v = int((f + 1.0) * m_precision / 2.0 );
	return j < v;
}

void VoxeledHeightfield::populateArray(Array3D<bool> *arr, int precision) 
{
	m_precision = precision;
	for (int i = 0; i<precision; i++) 
	{
		for (int j = 0; j<precision; j++) 
		{
			for (int k = 0; k<precision; k++) 
			{
				(*arr)(i,j,k) = isActive(i,j,k);
			}
		}
	}
}
