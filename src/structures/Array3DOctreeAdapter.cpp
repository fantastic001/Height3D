
#include "Array3DOctreeAdapter.hpp" 

Array3DOctreeAdapter::Array3DOctreeAdapter(Array3D<bool> &arr, bool compress) : 
	m_arr(&arr)
{
}

void Array3DOctreeAdapter::generate(bool compress) 
{
	generate(m_arr->getSizeX(), m_arr->getSizeY(), m_arr->getSizeZ(), compress);
}

bool Array3DOctreeAdapter::isActive(int i, int j, int k) 
{
	return m_arr->value(i,j,k);
}
