#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Vector
#include <boost/test/unit_test.hpp>

#include <core/Vector.hpp>

BOOST_AUTO_TEST_CASE( constructor )
{
	Vector v1(1.0, 1.0, 1.0, 1.0, true);
	BOOST_CHECK(v1.getX() == 1.0);
	BOOST_CHECK(v1.isColumn() == true);

	Vector v2(0.0, 0.0, 0.0, 0.0); 
	BOOST_CHECK(v2.getW() == 0.0);

	Vector v3(0);
	BOOST_CHECK(v3.getZ() == 0.0);

	Vector zero = Vector::zero();
	BOOST_CHECK(zero.getZ() == 0.0);
}


BOOST_AUTO_TEST_CASE( operators ) 
{
	Vector v1 = Vector(1.0, 1.0, 1.0, 1.0);
	BOOST_CHECK(v1.getX() == 1.0);
	BOOST_CHECK(v1.getY() == 1.0);
	BOOST_CHECK(v1.getZ() == 1.0);
	BOOST_CHECK(v1.getW() == 1.0);
	
	v1 = Vector(2.0, 4.0, 6.0, 8.0);
	BOOST_CHECK(v1.getX() == 2.0);
	BOOST_CHECK(v1.getY() == 4.0);
	BOOST_CHECK(v1.getZ() == 6.0);
	BOOST_CHECK(v1.getW() == 8.0);
	
	v1 = v1 + Vector(1.0, 0.0, 0.0, 0.0);
	BOOST_CHECK(v1.getX() == 3.0);
	BOOST_CHECK(v1.getY() == 4.0);
	BOOST_CHECK(v1.getZ() == 6.0);
	BOOST_CHECK(v1.getW() == 8.0);
	
	v1 = v1 - Vector(1.0, 0.0, 0.0, 0.0);
	BOOST_CHECK(v1.getX() == 2.0);
	BOOST_CHECK(v1.getY() == 4.0);
	BOOST_CHECK(v1.getZ() == 6.0);
	BOOST_CHECK(v1.getW() == 8.0);
}

BOOST_AUTO_TEST_CASE( cross )
{
	Vector v1(1.0, 1.0, 1.0);
	Vector v2(0.0, 2.0, 1.0);
	Vector result = v1.cross(v2);
	BOOST_CHECK(result.getX() == -1);
	BOOST_CHECK(result.getY() == -1);
	BOOST_CHECK(result.getZ() == 2);
}

BOOST_AUTO_TEST_CASE( dot ) 
{
	Vector v1(1.0, 1.0, 1.0, 1.0);
	Vector v2(1.0, 1.0, 1.0, 0.0);
	BOOST_CHECK(v1.dot(v2) == v2.dot(v1));
	BOOST_CHECK(v1.dot(v2) == 3.0);
}

BOOST_AUTO_TEST_CASE( transpose ) 
{
	Vector v1(1.0, 1.0, 1.0, 1.0);
	BOOST_CHECK(v1.transpose().isColumn() == false);
	BOOST_CHECK(v1.transpose().transpose().isColumn() == true);
}

