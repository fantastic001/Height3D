#ifndef HEIGHT3D_ABSTRACT_MODEL_HPP
#define HEIGHT3D_ABSTRACT_MODEL_HPP

#include <vector> 

#include "Buffer.hpp"

class AbstractModel 
{

public:
	void send(Buffer& vertexBuffer, Buffer& indexBuffer, Buffer& colorBuffer, Buffer& textureBuffer); 

protected:
	virtual std::vector<float> genVertices() = 0; 
	virtual std::vector<float> genIndices() = 0; 
	virtual std::vector<float> genVertexColors() = 0; 
	virtual std::vector<float> genTextureCoordinates() = 0; 


};

#endif // HEIGHT3D_ABSTRACT_MODEL_HPP
