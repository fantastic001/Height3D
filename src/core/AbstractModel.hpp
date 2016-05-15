#ifndef HEIGHT3D_ABSTRACT_MODEL_HPP
#define HEIGHT3D_ABSTRACT_MODEL_HPP

#include <vector> 

#include "Buffer.hpp"

class AbstractModel 
{

	int m_count;
public:
	void send(Buffer* vertexBuffer, Buffer* indexBuffer, Buffer* colorBuffer, Buffer* textureBuffer, Buffer* normalsBuffer = NULL); 
	int count();

protected:
	/*
	Should return std::vector populated with vertex locations. 
	Every vertex is defined by its location using triple coordinates (x,y,z)

	For example, if we have 3 vertices, our std::vector has to have size of 9 
	*/
	virtual std::vector<float> genVertices() = 0; 
	
	/*
	Should return std::vector populated with indices which define order of drawing. Size of this vector has to be multiple of 3.
	*/
	virtual std::vector<int> genIndices() = 0; 
	
	/*
	Should return color values for each vertex from vertex array. Size has to be (vertexCount) * 3
	*/
	virtual std::vector<float> genVertexColors() = 0; 
	
	/*
	Should return std::vector populated with texture coordinates in range [0.0, 1.0]. Size is vertexCount * 2
	*/
	virtual std::vector<float> genTextureCoordinates() = 0; 

	/*
	For each vertex define normal vector
	*/
	virtual std::vector<float> genNormals();


};

#endif // HEIGHT3D_ABSTRACT_MODEL_HPP
