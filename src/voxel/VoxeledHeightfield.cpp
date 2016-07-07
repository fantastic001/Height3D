
#include "VoxeledHeightfield.hpp"

Array3D<bool> VoxeledHeightfield::generateArray(int precision) 
{
	Array3D<bool> a(precision, precision, precision);
	for (int i = 0; i<precision; i++) 
	{
		for (int j = 0; j<precision; j++) 
		{
			for (int k = 0; k<precision; k++) 
			{
				float f = function(2*i / float(precision) - 1.0, 2*k / float(precision) - 1.0);
				int v = int((f + 1.0) * precision / 2.0 );
				if (j <= v) a(i,j,k) = true; 
				else a(i,j,k) = false;
			}
		}
	}
	return a;
}

Octree* VoxeledHeightfield::generateOctree(int depth) 
{
	
}
