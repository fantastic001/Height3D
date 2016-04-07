#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Vector
#include <boost/test/unit_test.hpp>

#include <core/Vector.hpp>

BOOST_AUTO_TEST_CASE( constructor )
{
	Vector v(1.0, 1.0, 1.0, 1.0, true);
	BOOST_CHECK(v.getX() == 1.0);
}
