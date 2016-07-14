
#include "erode.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

void make_hole(Array3D<bool>& arr) 
{
	srand (time(NULL));
	int sizex = arr.getSizeX();
	int sizey = arr.getSizeY();
	int sizez = arr.getSizeZ();
	
	int i,j,k;


	int direction; 

	do 
	{
		i = rand() % sizex;
		j = rand() % sizey;
		k = rand() % sizez; 
		direction = rand() % 6;
	}
	while (! arr(i,j,k));
	int di=0,dj=0,dk=0;
	switch (direction) 
	{
		case 0: di = 1; break;
		case 1: di = -1; break;
		case 2: dj = 1; break;
		case 3: dj = -1; break;
		case 4: dk = 1; break;
		case 5: dk = -1; break;
	}
	int l = 0;
	while (arr(i,j,k) && i+di*l<sizex && j + dj*l < sizey && k + dk*l < sizez
		&& i >= 0 && j >= 0 && k >= 0
	) 
	{
		arr(i + di*l, j + dj*l, k + dk*l) = false; 
		l++;
		cout << i + di*l << " " << j + dj*l << " " << k + dk*l << endl;
	}
}

Array3D<bool> erode(Array3D<bool> &arr) 
{
	Array3D<bool> *res = new Array3D<bool>(arr.getSizeX(), arr.getSizeY(), arr.getSizeZ());; 
	for (int i = 0; i<arr.getSizeX(); i++) 
	{
		for (int j = 0; j<arr.getSizeY(); j++) 
		{
			for (int k = 0; k<arr.getSizeZ(); k++) 
			{
				if (! arr(i,j,k)) 
				{
					(*res)(i,j,k) = arr(i,j,k);
					if (i<arr.getSizeX() - 1) (*res)(i+1,j,k) = false;
					if (i>0) (*res)(i-1,j,k) = false;
					if (j < arr.getSizeY() - 1) (*res)(i,j+1,k) = false;
					if (j>0) (*res)(i,j-1,k) = false; 
					if (k < arr.getSizeZ() - 1) (*res)(i,j,k+1) = false;
					if (k>0) (*res)(i,j,k-1) = false;
				}
				else 
				{
					(*res)(i,j,k) = arr(i,j,k);
				}
			}
		}
	}
	return *res; 
}
