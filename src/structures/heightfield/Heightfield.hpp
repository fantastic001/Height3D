
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_HEIGHTFIELD_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_HEIGHTFIELD_HPP

#include <utility>
#include <functional>
using namespace std;

class Heightfield 
{
	float *m_top;
	float *m_bottom;
	int m_precision;
	int N;

public:
	Heightfield(int precision); 
	~Heightfield();

	/*
	Values in the following methods must be between -1 and 1 (inclusive)
	*/
	void setTopLevel(float x, float z, float y);
	void setBottomLevel(float x, float z, float y);
	void setTopLevel(int i, int j, float y);
	void setBottomLevel(int i, int j, float y);

	float getTopLevel(float x, float z);
	float getBottomLevel(float x, float z);
	
	float getTopLevel(int i, int j);
	float getBottomLevel(int i, int j);

	// This function traverses whole heightfield and assigns values to top and bottom
	// it recieves function which returns pair<float, float> which is pair of pair (bottom, top) for given parameters x,z
	void assign(function<pair<float, float> (float, float)>);

};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_HEIGHTFIELD_HPP
