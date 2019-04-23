
#ifndef HEIGHT3D_MATRIX_HPP
#define HEIGHT3D_MATRIX_HPP

#include "Vector.hpp" 

class Matrix 
{
	float data[4][4];

public: 
	Matrix(
		float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44
	);
	
	/// Create matrix populated with given value
	Matrix(float a); 

	float getElement(int i, int j); 
	
	/// Matrix multiplication this * m
	Matrix mult(Matrix m); 

	/// Matrix-vector multiplication
	Vector mult(Vector v); 
	
	/// Returns linear transformation which does scaling on x,y and z axis
	static Matrix scale(float a, float b, float c);

	/// Returns linear transformation which does rotation around specified axis with angle alpha (degrees)
	static Matrix rotation(float alpha, Vector axis);

	/// Returns linear transformation which does translation in direction of specified vector 
	static Matrix translation(Vector v);
	
	/// Copy matrix
	Matrix& operator=(Matrix m);
};

#endif // HEIGHT3D_MATRIX_HPP
