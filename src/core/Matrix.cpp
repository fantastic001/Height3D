
#include "Matrix.hpp" 

#include <cmath>

using namespace std; 


Matrix::Matrix(
	float a11, float a12, float a13, float a14,
	float a21, float a22, float a23, float a24,
	float a31, float a32, float a33, float a34,
	float a41, float a42, float a43, float a44
) 
{
	data[0][0] = a11; 
	data[0][1] = a12;
	data[0][2] = a13;
	data[0][3] = a14;
	data[1][0] = a21;
	data[1][1] = a22;
	data[1][2] = a23;
	data[1][3] = a24;
	data[2][0] = a31;
	data[2][1] = a32;
	data[2][2] = a33;
	data[2][3] = a34;
	data[3][0] = a41;
	data[3][1] = a42;
	data[3][2] = a43;
	data[3][3] = a44;
}

Matrix::Matrix(float a) : Matrix(a,a,a,a,
				a,a,a,a,
				a,a,a,a,
				a,a,a,a)
{
	
}

float Matrix::getElement(int i, int j) 
{
	return data[i][j];
}

Matrix Matrix::mult(Matrix m) 
{
	float mat[4][4];
	for (int i = 0; i<4; i++) 
	{
		for (int j = 0; j<4; j++) 
		{
			mat[i][j] = 0.0;
			for (int k = 0; k<4; k++) 
			{
				mat[i][j] += data[i][k]*m.getElement(k, j);
			}
		}
	}
	return Matrix(
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]
	);
}

Vector Matrix::mult(Vector v) 
{
	return Vector(
		data[0][0]*v.getX() + data[0][1]*v.getY() + data[0][2]*v.getZ() + data[0][3]*v.getW(),
		data[1][0]*v.getX() + data[1][1]*v.getY() + data[1][2]*v.getZ() + data[1][3]*v.getW(),
		data[2][0]*v.getX() + data[2][1]*v.getY() + data[2][2]*v.getZ() + data[2][3]*v.getW(),
		data[3][0]*v.getX() + data[3][1]*v.getY() + data[3][2]*v.getZ() + data[3][3]*v.getW()
	);
}

Matrix Matrix::scale(float a, float b, float c) 
{
	return Matrix(
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		0, 0, 0, 1
	);
}
Matrix Matrix::rotation(float alpha, Vector axis) 
{
	float c = cos(alpha);
	float s = sin(alpha); 
	float omc = 1 - c;
	float u = axis.getX();
	float v = axis.getY();
	float w = axis.getZ();
	return Matrix(
		u*u + (1 - u*u)*c, u*v*omc - w*s, u*w*omc + v*s, 0,
		u*v*omc + w*s, v*v + (1 - v*v)*c, v*w*omc - u*s, 0,
		u*w*omc - v*s, v*w*omc + u*s, w*w + (1 - w*w)*c, 0,
		0, 0, 0, 1
	);
}

Matrix Matrix::translation(Vector v) 
{
	return Matrix(
		1, 0, 0, v.getX(),
		0, 1, 0, v.getY(),
		0, 0, 1, v.getZ(),
		0, 0, 0, 1
	);
}

Matrix& Matrix::operator=(Matrix m) 
{
	for (int i = 0; i<4; i++) 
	{
		for (int j = 0; j<4; j++) 
		{
			data[i][j] = m.getElement(i,j);
		}
	}
	return *this;
}
