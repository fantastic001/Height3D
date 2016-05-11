
#ifndef HEIGHT3D_MATERIAL_HPP
#define HEIGHT3D_MATERIAL_HPP

#include "Color.hpp"

typedef struct 
{
	Color ka;
	Color kd;
	Color ks;
	float alpha;
	float beta;
	float shineness;
} Material;

#endif // HEIGHT3D_MATERIAL_HPP
