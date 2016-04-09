#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Matrix.hpp>
#include <iostream>

using namespace std; 

BOOST_AUTO_TEST_CASE( matrix_constructor )
{
	Matrix m1(0, 0, 0, 0,
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0);
	BOOST_CHECK(m1.getElement(2, 1) == 1);

	Matrix m2( 1 ); 
	BOOST_CHECK(m2.getElement(2,2) == 1);
}


BOOST_AUTO_TEST_CASE( matrix_multiplication_vector ) 
{
	Matrix m(
		1, 1, 1, 1,
		1, 1, 1, 1, 
		1, 1, 1, 1, 
		1, 1, 1, 1
	);
	Vector v(1, 1, 1, 1); 
	Vector result = m.mult(v);
	BOOST_CHECK(result.getX() == 4);
	BOOST_CHECK(result.getY() == 4);
	BOOST_CHECK(result.getZ() == 4);
	BOOST_CHECK(result.getW() == 4);
}

BOOST_AUTO_TEST_CASE( matrix_multiplication_matrix ) 
{

	Matrix m(
		1, 1, 1, 1,
		1, 1, 1, 1, 
		1, 1, 1, 1, 
		1, 1, 1, 1
	);
	Matrix result = m.mult(m);
	BOOST_CHECK(result.getElement(3,3) == 4);
}


BOOST_AUTO_TEST_CASE( matrix_rotation ) 
{
	const float pi = 3.14159265359;
	// we rotate it by 2pi about unit axis (1, 0, 0), it should stay the same 
	float alpha = 2*pi;
	Vector v(1.0, 2.0, 3.0);
	Vector result = Matrix::rotation(alpha, Vector(1.0, 0, 0)).mult(v);
	BOOST_CHECK_CLOSE(v.getX(), result.getX(), 0.1);
	BOOST_CHECK_CLOSE(v.getY(), result.getY(), 0.1);
	BOOST_CHECK_CLOSE(v.getZ(), result.getZ(), 0.1);
	BOOST_CHECK_CLOSE(v.getW(), result.getW(), 0.1);
}

BOOST_AUTO_TEST_CASE( matrix_scaling ) 
{
	// we scale it by 10 on every axis
	Vector v(1, 2, 3);
	Vector result = Matrix::scale(10, 10, 10).mult(v);
	BOOST_CHECK(result.getX() == 10);
	BOOST_CHECK(result.getY() == 20);
	BOOST_CHECK(result.getZ() == 30);
}

BOOST_AUTO_TEST_CASE( matrix_translation ) 
{
	// we translate it by (1,1,2)
	Vector v(1.0f, 2.0f, 3.0f);
	Vector t(1.0f, 1.0f, 2.0f);
	Vector result = Matrix::translation(t).mult(v);
	BOOST_CHECK(result.getX() == 2);
	BOOST_CHECK(result.getY() == 3);
	BOOST_CHECK(result.getZ() == 5);
}
