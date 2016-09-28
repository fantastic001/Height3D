
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
							h->addLevel();
							added = true;
						}
						h->setTop(levels+1,i,j,k->bottom(x,z));
						h->setBottom(levels+1,i,j,h->getBottom(l,i,j));
						h->setBottom(levels,i,j,k->top(x,z));
						h->setTop(levels,i,j,h->getTop(l,i,j));
						h->setTop(l,i,j,-1);
						h->setBottom(l,i,j,-1);
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
	// we now have to fix h(l,i,j) if it is on the edge to ommit holes in primary level 
	bool*** change = new bool** [levels];
	for (int l = 0; l<levels; l++) {
		change[l] = new bool* [size+1];
		for (i=0; i<=size; i++) 
		{
			change[l][i] = new bool [size+1];
			for (j=0; j<=size; j++) change[l][i][j] = false; 
		}
	}
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
					if (added && 
						h->getBottom(levels+1,i,j) <= k->bottom(x,z) 
						&& k->bottom(x,z) <= k->top(x,z) 
						&& k->top(x,z) <= h->getTop(levels,i,j)
					)
					{
						if (
							(i<size && h->getTop(l,i+1,j) != -1) || 
							(j<size && h->getTop(l,i,j+1) != -1) || 
							(i>0 && h->getTop(l,i-1,j) != -1) || 
							(j>0 && h->getTop(l,i,j-1) != -1) ||
							
							(i<size-1 && h->getTop(l,i+2,j) != -1) || 
							(j<size-1 && h->getTop(l,i,j+2) != -1) || 
							(i>1 && h->getTop(l,i-2,j) != -1) || 
							(j>1 && h->getTop(l,i,j-2) != -1) 
						
						)
						{
							change[l][i][j] = true;
						}
					}
				}
			}
		}
	}
	for (i=0; i<=size; i++)  for (j=0; j<=size; j++) for (int l = 0; l<levels; l++) if (change[l][i][j]) 
	{
		
		h->setTop(l,i,j,h->getTop(levels,i,j));
		h->setBottom(l,i,j,h->getBottom(levels+1, i,j));
	}

}
