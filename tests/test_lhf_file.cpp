

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <structures/heightfield/LayeredHeightfield.hpp>

static  bool check(LayeredHeightfield *h1, LayeredHeightfield *h2)  
{
	if (h1->levelCount() == h2->levelCount()) 
	{
		if (h1->getPrecision() == h2->getPrecision()) 
		{
			bool ok = true; 
			for (int l = 0; l<h1->levelCount(); l++) 
			{
				for (int i = 0; i<=h1->getPrecision(); i++) 
				{
					for (int j = 0; j<=h1->getPrecision(); j++) 
					{
						ok = ok && h1->getTop(l,i,j) == h2->getTop(l,i,j) && 
							h1->getBottom(l,i,j) == h2->getBottom(l,i,j);
					}
				}
			}
			return ok; 
			
		}
		else 
		{
			return false;
		}

	}
	else 
	{
		return false; 
	}
}

BOOST_AUTO_TEST_CASE( lhf_file_storage_test )
{
	LayeredHeightfield *h1 = new LayeredHeightfield(128);
	h1->addLevel();
	h1->addLevel();
	for (float x = -1; x<=1.0; x += 2.0/128) 
	{
		for (float z = -1; z<=1.0; z += 2.0/128) 
		{
			h1->set(0,x,z,x+z, x+z+1);
			h1->set(1,x,z,x+z+2, x+z+3);
		}
	}
	h1->writeToFile("layered_heightfield_storage_file_test.bin");
	LayeredHeightfield* h2 = LayeredHeightfield::readFromFile("layered_heightfield_storage_file_test.bin");
	BOOST_CHECK(check(h1, h2));
}

