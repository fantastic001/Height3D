
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP

#include "ImplicitLayeredHeightfieldGenerator.hpp"

#include <core/Array3D.hpp>

class Array3DLayeredHeightfieldAdapter : public ImplicitLayeredHeightfieldGenerator
{
	Array3D<bool>* m_arr; 
	int m_precision;
public:
	Array3DLayeredHeightfieldAdapter(Array3D<bool> arr);
	void generate();

protected:
	using ImplicitLayeredHeightfieldGenerator::generate;
	bool isActive(float x, float y, float z);
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_ARRAY3D_LAYERED_HEGHTFIELD_ADAPTER_HPP
