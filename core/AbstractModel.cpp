
#include "AbstractModel.hpp"

using namespace std;

void AbstractModel::send(Buffer* vertexBuffer, Buffer* indexBuffer, Buffer* colorBuffer, Buffer* textureBuffer) 
{
	vector<float> 
	vertices = genVertices(), 
	colors = genVertexColors(), 
	coords = genTextureCoordinates(); 

	vector<int> indices = genIndices();
	m_count = indices.size();
	
	vertexBuffer->bind(); 
	vertexBuffer->sendData(vertices); 

	indexBuffer->bind(); 
	indexBuffer->sendData(indices); 

	colorBuffer->bind();
	colorBuffer->sendData(colors);

	textureBuffer->bind();
	textureBuffer->sendData(coords);

}

int AbstractModel::count() 
{
	return m_count;
}
