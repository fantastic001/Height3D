
#ifndef HEIGHT3D_VECTOR_HPP
#define HEIGHT3D_VECTOR_HPP

class Vector 
{
	float x,y,z,w; 
	bool column; 

public: 
	Vector(float x1, float y1, float z1, float w1); 
	Vector(float x1, float y1, float z1, float w1, bool column1);
	Vector(float x1, float y1, float z1);
	Vector(float a); 

	Vector& operator= (Vector v); 
	Vector& operator+ (Vector v);
	Vector& operator- (Vector v); 
	
	float dot(Vector v); 

	/*
	Computes cross product
	*/
	Vector cross(Vector v);

	Vector transpose();

	/*
	Return normalized vector (except w-component)
	*/
	Vector normalized();

	float getX();
	float getY();
	float getZ();
	float getW();
	bool isColumn();

	static Vector zero(); 
};

#endif // HEIGHT3D_VECTOR_HPP
