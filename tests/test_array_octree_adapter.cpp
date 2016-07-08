

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Array3D.hpp>
#include <structures/Array3DOctreeAdapter.hpp>

void traverse_octree(int &count, OctreeNode* node) 
{
	if (! node->hasChilds()) count++;
	if (node->getChild(false, false, false) != NULL) traverse_octree(count, node->getChild(false, false, false));
	if (node->getChild(false, false, true) != NULL) traverse_octree(count, node->getChild(false, false, true));
	if (node->getChild(false, true, false) != NULL) traverse_octree(count, node->getChild(false, true, false));
	if (node->getChild(false, true, true) != NULL) traverse_octree(count, node->getChild(false, true, true));

	if (node->getChild(true, false, false) != NULL) traverse_octree(count, node->getChild(true, false, false));
	if (node->getChild(true, false, true) != NULL) traverse_octree(count, node->getChild(true, false, true));
	if (node->getChild(true, true, false) != NULL) traverse_octree(count, node->getChild(true, true, false));
	if (node->getChild(true, true, true) != NULL) traverse_octree(count, node->getChild(true, true, true));
}

BOOST_AUTO_TEST_CASE( array_octree_test )
{
	Array3D<bool> a(4,4,4);
	for (int i = 0; i<4; i++) for (int j = 0; j<4; j++) for (int k = 0; k<4; k++) a(i,j,k) = false; 
	a(2,2,2) = true;
	Array3DOctreeAdapter adapter(a);
	adapter.generate();
	OctreeNode* root = adapter.getRoot();
	
	int count = 0; 
	traverse_octree(count, root); 
	BOOST_CHECK_EQUAL(count, 64);
}

BOOST_AUTO_TEST_CASE( array_octree_compress_test )
{
	Array3D<bool> a(4,4,4);
	int i,j,k;
	for (i = 0; i<4; i++) for (j = 0; j<4; j++) for (k = 0; k<4; k++) a(i,j,k) = false; 
	for (i=2; i<4; i++) for (j=2; j<4; j++) for (k=2; k<4; k++) a(i,j,k) = true; 
	Array3DOctreeAdapter adapter(a);
	adapter.generate(true);
	OctreeNode* root = adapter.getRoot();
	BOOST_CHECK(root->getChild(true, true, true)->active());
	BOOST_CHECK(! root->getChild(true, true, true)->hasChilds());
	
	int count = 0; 
	traverse_octree(count, root);
	BOOST_CHECK_EQUAL(count, 8);
}

BOOST_AUTO_TEST_CASE( array_octree_large_test )
{
	int i,j,k;

	Array3D<bool> a(8,8,8);
	for (i = 0; i<8; i++) for (j = 0; j<8; j++) for (k = 0; k<8; k++) a(i,j,k) = false; 
	a(2,2,2) = true;
	Array3DOctreeAdapter adapter(a);
	adapter.generate();
	OctreeNode* root = adapter.getRoot();

	int count = 0; 
	traverse_octree(count, root); 
	BOOST_CHECK_EQUAL(count, 512);
}
