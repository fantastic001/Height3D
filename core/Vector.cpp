
#include "common.hpp"
#include "Vector.hpp" 


Vector::Vector(float x1, float y1, float z1, float w1) 
{
	column = true; 
	x = x1; 
	y = y1; 
	z = z1; 
	w = w1;
}
Vector::Vector(float x1, float y1, float z1) : Vector(x1, y1, z1, 1)
{
}

Vector::Vector(float x1, float y1, float z1, float w1, bool column1) 
{
	column = column1;
	x = x1;
	y = y1; 
	z = z1; 
	w = w1; 
}

Vector::Vector(float a) 
{
	column = true; 
	x = a; 
	y = a; 
	z = a; 
	w = a; 
}

Vector& Vector::operator= (Vector v) 
{
	x = v.getX();
	y = v.getY(); 
	z = v.getZ();
	w = v.getW();
	column = v.isColumn();
}

Vector& Vector::operator+ (Vector v) 
{
	return *(new Vector(x + v.getX(), y + v.getY(), z + v.getZ(), w + v.getW(), column));
}
Vector& Vector::operator- (Vector v) 
{
	return *(new Vector(x - v.getX(), y - v.getY(), z - v.getZ(), w - v.getW(), column));
}
	
float Vector::dot(Vector v) 
{
	return x*v.getX() + y*v.getY() + z*v.getZ() + w*v.getW();
}
Vector Vector::transpose() 
{
	return Vector(x,y,z,w,!column);
}

float Vector::getX() 
{
	return x;
}

float Vector::getY() 
{
	return y; 
}

float Vector::getZ() 
{
	return z;
}

float Vector::getW() 
{
	return w; 
}

bool Vector::isColumn() 
{
	return column;
}

Vector Vector::zero() 
{
	return Vector(0.0);
}
