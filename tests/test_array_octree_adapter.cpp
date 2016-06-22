

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Array3D.hpp>
#include <structures/Array3DOctreeAdapter.hpp>

BOOST_AUTO_TEST_CASE( array_octree_test )
{
	Array3D<bool> a(3,3,3);
	a(1,1,1) = true;
	Array3DOctreeAdapter adapter(a);
	OctreeNode* root = adapter.getRoot();
	BOOST_CHECK(root->active());
	BOOST_CHECK(! root->getChild(true, true, true)->active());
}
