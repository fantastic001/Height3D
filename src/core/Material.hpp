
#ifndef HEIGHT3D_MATERIAL_HPP
#define HEIGHT3D_MATERIAL_HPP

#include "Color.hpp"

typedef struct Material
{
	Color ka;
	Color kd;
	Color ks;
	float alpha;
	float beta;
	float gamma;
	float shininess;
	Material() 
	{
		ka = Color(0,0,0);
		ks = Color(0,0,0);
		kd = Color(0,0,0);
		alpha = gamma = beta = 1;
		shininess = 0;
	}
	Material(Color _ka, Color _kd, Color _ks, float _alpha, float _beta, float _gamma, float _shininess) 
	{
		ka = _ka;
		kd = _kd; 
		ks = _ks;
		alpha = _alpha;
		beta = _beta;
		gamma = _gamma;
		shininess = _shininess;
	} 
} Material;

#endif // HEIGHT3D_MATERIAL_HPP
