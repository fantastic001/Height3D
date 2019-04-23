#ifndef HEIGHT3D_ABSTRACT_MODEL_HPP
#define HEIGHT3D_ABSTRACT_MODEL_HPP

#include <vector> 

#include "Buffer.hpp"
/*
 *! This class represents abstract model which is inherited to implement other models. Each model has its vertex positions, color definition for every vertex if texture
 * is not used, normal definitions for every vertex, texture coordinates to be used when texture is defined inside the shader and also order of vertices to be drawn..
 * */
class AbstractModel 
{

	int m_count;
public:
	/*!
	 * \brief Send generated data into buffers
	 *
	 * \param vertexBuffer is pointer to Buffer object holding address for buffer to be used for vertices
	 * \param indexBuffer is pointer to Buffer object holding address for buffer to be used for indices
	 * \param colorBuffer is pointer to Buffer object holding address for buffer to be used for colors
	 * \param textureBuffer is pointer to Buffer object holding address for buffer to be used for texture coordinates
	 * \param normalsBuffer is pointer to Buffer object holding address for buffer to be used for normals
	 * */
	void send(Buffer* vertexBuffer, Buffer* indexBuffer, Buffer* colorBuffer, Buffer* textureBuffer, Buffer* normalsBuffer = NULL); 
	
	/*!
	 * Returns how many times vertices are drawn (size of index array which will be put into indexBuffer)
	 * */
	int count();

	/// Returns number of vertices
	int countVertices();

	/// Returns number of triangles which will be drawn using this model
	int countTriangles();

protected:
	/*!
	Should return std::vector populated with vertex locations. 
	Every vertex is defined by its location using triple coordinates (x,y,z)

	For example, if we have 3 vertices, our std::vector has to have size of 9 
	*/
	virtual std::vector<float> genVertices() = 0; 
	
	/*!
	Should return std::vector populated with indices which define order of drawing. Size of this vector has to be multiple of 3.
	*/
	virtual std::vector<int> genIndices() = 0; 
	
	/*!
	Should return color values for each vertex from vertex array. Size has to be (vertexCount) * 4

	Colors are in format (r,g,b,a)
	*/
	virtual std::vector<float> genVertexColors() = 0; 
	
	/*!
	Should return std::vector populated with texture coordinates in range [0.0, 1.0]. Size is vertexCount * 2
	*/
	virtual std::vector<float> genTextureCoordinates() = 0; 

	/*!
	For each vertex define normal vector. Size of returned vector has to be 2 * vertexCount.
	*/
	virtual std::vector<float> genNormals();


};

#endif // HEIGHT3D_ABSTRACT_MODEL_HPP
