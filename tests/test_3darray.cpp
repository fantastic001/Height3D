
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Array3D.hpp>
#include <iostream>

using namespace std; 

BOOST_AUTO_TEST_CASE( array3d_constructor )
{
	Array3D<int> a(10, 10, 10);
	BOOST_CHECK(a.getSizeX() == 10);
}

BOOST_AUTO_TEST_CASE( array3d_set_get )
{
	Array3D<int> a(10, 10, 10);
	a(5,4,3) = 100;
	BOOST_CHECK(a(5,4,3) == 100);
}
