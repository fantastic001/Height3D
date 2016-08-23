
#ifndef HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP
#define HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP

#include <vector>

#include "Heightfield.hpp"

class LayeredHeightfield 
{
	std::vector<Heightfield*> *m_layers; 
	int m_precision; 

public:
	LayeredHeightfield(int precision);
	~LayeredHeightfield();

	void writeToFile(char* path);
	static LayeredHeightfield* readFromFile(char* path);

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

	float toContinious(int i);

	int getPrecision();
};

#endif // HEIGHT3D_STRUCTURES_HEIGHTFIELD_LAYERED_HEIGHTFIELD_HPP
