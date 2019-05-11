
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP

#include <vector>
#include <functional>

#include "Heightfield.hpp"
using namespace std;

class LayeredHeightfield 
{
	std::vector<Heightfield*> *m_layers; 
	int m_precision; 

public:
	LayeredHeightfield(int precision);
	~LayeredHeightfield();

	void writeToFile(const char* path);
	static LayeredHeightfield* readFromFile(const char* path);

	Heightfield* levelAt(int index); 
	int levelCount();
	void addLevel();
	void set(int level, float x, float z, float yb, float yt);

	float getTop(int level, float x, float z);
	float getBottom(int level, float x, float z);
	
	float getTop(int level, int i, int j);
	float getBottom(int level, int i, int j);

	void setTop(int level, float x, float z, float y);
	void setBottom(int level, float x, float z, float y);
	
	void setTop(int level, int i, int j, float y);
	void setBottom(int level, int i, int j, float y);
	/// Convert given index in array to representation in x,z plane
	float toContinious(int i);

	int getPrecision();

	int countLeftRightEdges();
	int countForwardBackwardEdges();

	/// This function iterates over field on all levels and assigns apropirate value for top and bottom
	/// it recieves function (int level, float x, float z) -> pair<float, float> (bottom, top)
	void assign(function<pair<float, float> (int, float, float)>);
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP
