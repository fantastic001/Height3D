

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <core/Array3D.hpp>
#include <structures/octree/Array3DOctreeAdapter.hpp>
#include <structures/octree/OctreeFileStorage.hpp>

static  bool check(OctreeNode* node1, Octree* node2) 
{
	bool ok = node1->active() == node2->active() && node1->start() == node2->start() && node1->end() == node2->end() 
		&& node1->hasChilds() == node2->hasChilds();
	if (node1->hasChilds()) 
	{
		for (int i = 0; i<8; i++) 
		{
			ok = ok && check(node1->getChild(i), node2->getChild(i));
		}
	}
	return ok;
}

BOOST_AUTO_TEST_CASE( octree_file_storage_test )
{
	Array3D<bool> a(4,4,4);
	for (int i = 0; i<4; i++) for (int j = 0; j<4; j++) for (int k = 0; k<4; k++) a(i,j,k) = false; 
	a(2,2,2) = true;
	Array3DOctreeAdapter adapter(a);
	adapter.generate();
	OctreeNode* root = adapter.getRoot();
	
	OctreeFileStorage writer("file_octree_storage_test.bin", true);
	writer.write(root);
	writer.close();

	OctreeFileStorage reader("file_octree_storage_test.bin");
	OctreeNode* root2 = reader.read();

	BOOST_CHECK(check(root, root2));
}

