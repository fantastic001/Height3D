
#include "AbstractModel.hpp"

using namespace std;

void AbstractModel::send(Buffer& vertexBuffer, Buffer& indexBuffer, Buffer& colorBuffer, Buffer& textureBuffer) 
{
	vector<float> 
	vertices = genVertices(), 
	indices = genIndices(), 
	colors = genVertexColors(), 
	coords = genTextureCoordinates(); 
	
	vertexBuffer.bind(); 
	vertexBuffer.sendData(vertices); 

	indexBuffer.bind(); 
	indexBuffer.sendData(indices); 

	colorBuffer.bind();
	colorBuffer.sendData(colors);

	textureBuffer.bind();
	textureBuffer.sendData(coords);

}
