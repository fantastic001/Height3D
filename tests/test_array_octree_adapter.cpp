

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Array3D.hpp>
#include <structures/Array3DOctreeAdapter.hpp>

BOOST_AUTO_TEST_CASE( array_octree_test )
{
	Array3D<bool> a(3,3,3);
	for (int i = 0; i<3; i++) for (int j = 0; j<3; j++) for (int k = 0; k<3; k++) a(i,j,k) = false; 
	a(1,1,1) = true;
	Array3DOctreeAdapter adapter(a);
	OctreeNode* root = adapter.getRoot();
	BOOST_CHECK(root->active());
	BOOST_CHECK( !root->getChild(true, true, true)->active());
	BOOST_CHECK( root->getChild(true, true, true)->getChild(true, true, true) == NULL);
}

BOOST_AUTO_TEST_CASE( array_octree_large_test )
{
	int i,j,k;

	Array3D<bool> a(5,5,5);
	for (i = 0; i<3; i++) for (j = 0; j<3; j++) for (k = 0; k<3; k++) a(i,j,k) = false; 
	a(2,2,2) = true;
	Array3DOctreeAdapter adapter(a);
	OctreeNode* root = adapter.getRoot();
	BOOST_CHECK(root->active());
	BOOST_CHECK(! root->getChild(true, true, true)->active());
	BOOST_CHECK( root->getChild(true, true, true)->getChild(true, true, true) == NULL);
}
