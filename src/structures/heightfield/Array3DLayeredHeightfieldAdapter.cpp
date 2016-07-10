
#include "Array3DLayeredHeightfieldAdapter.hpp"


Array3DLayeredHeightfieldAdapter::Array3DLayeredHeightfieldAdapter(Array3D<bool> arr) 
{
	m_precision = arr.getSizeX() - 1;
	m_arr = new Array3D<bool>(m_precision, m_precision, m_precision);
	(*m_arr) = arr;

}

bool Array3DLayeredHeightfieldAdapter::isActive(float x, float y, float z) 
{
	return (*m_arr)(int((m_precision - 1) * (x+1) / 2), int((m_precision - 1) * (y+1) / 2), int((m_precision - 1) * (z+1) / 2));
	
}

void Array3DLayeredHeightfieldAdapter::generate()
{
	return generate(m_precision);
}

