
#include "CaveGenerator.hpp" 

void CaveGenerator::generate(Kernel *k, LayeredHeightfield *h) 
{
	int size = h->getPrecision(); 
	bool added = false; 
	int i,j;
	int levels = h->levelCount();
	for (i=0; i<=size; i++) 
	{
		for (j=0; j<=size; j++) 
		{
			float x = h->toContinious(i);
			float z = h->toContinious(j);
			if (k->defined(x,z)) 
			{
				for (int l = 0; l<levels; l++) 
				{
					if (
						h->getBottom(l,i,j) <= k->bottom(x,z) 
						&& k->bottom(x,z) < h->getTop(l,i,j) 
						&& h->getTop(l,i,j) <= k->top(x,z)
					) 
					{
						h->setTop(l,i,j,k->bottom(x,z));
					}
					else if (
						h->getBottom(l,i,j) <= k->bottom(x,z) 
						&& k->bottom(x,z) <= k->top(x,z) 
						&& k->top(x,z) <= h->getTop(l,i,j)
					) 
					{
						if (!added) 
						{
							h->addLevel();
							added = true;
						}
						float tmp = h->getTop(l,i,j);
						h->setTop(l,i,j,k->bottom(x,z));
						h->setBottom(levels,i,j,k->top(x,z));
						h->setTop(levels,i,j,tmp);
					}
					else if (
						k->bottom(x,z) <= h->getBottom(l,i,j) 
						&& h->getBottom(l,i,j) < k->top(x,z) 
						&& k->top(x,z) <= h->getTop(l,i,j)
					) 
					{
						h->setBottom(l,i,j,k->top(x,z));
					}
					else if (
						k->bottom(x,z) <= h->getBottom(l,i,j) 
						&& h->getTop(l,i,j) <= k->top(x,z)
					)
					{
						h->setTop(l,i,j,-1);
						h->setBottom(l,i,j, -1);
					}
				}
			}
		}
	}
}
