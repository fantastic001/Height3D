
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP

#include "LayeredHeightfield.hpp"
#include <core/Array3D.hpp>
/// Convert voxel representation to layered heightfield representation
class Array3DLayeredHeightfieldAdapter 
{
	Array3D<bool>* m_arr; 
	int m_precision;
	LayeredHeightfield* m_h;
public:
	Array3DLayeredHeightfieldAdapter(Array3D<bool> arr);
	void generate();
	LayeredHeightfield* getField(); 

	bool isActive(int i, int j, int k);
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP
