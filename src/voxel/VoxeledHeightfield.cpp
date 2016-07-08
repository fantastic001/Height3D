
#include "VoxeledHeightfield.hpp"
#include <structures/Array3DOctreeAdapter.hpp>


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

Octree* VoxeledHeightfield::generateOctree(int depth) 
{
	Array3D<bool> a = generateArray(128);
	Array3DOctreeAdapter adapter(a, true);
	return adapter.getRoot();
}

bool VoxeledHeightfield::isActive(int i, int j, int k) 
{
	float f = function(2*i / float(m_precision) - 1.0, 2*k / float(m_precision) - 1.0);
	int v = int((f + 1.0) * m_precision / 2.0 );
	return j <= v;
}
