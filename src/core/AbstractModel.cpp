
#include "AbstractModel.hpp"

using namespace std;

void AbstractModel::send(Buffer* vertexBuffer, Buffer* indexBuffer, Buffer* colorBuffer, Buffer* textureBuffer, Buffer* normalsBuffer) 
{
	vector<float> 
	vertices = genVertices(), 
	colors = genVertexColors(), 
	coords = genTextureCoordinates(); 
	vector<Vector> normals = genNormals();

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
	if (normalsBuffer != NULL)
	{
		normalsBuffer->bind();
		normalsBuffer->sendData(normals);
	}

}

int AbstractModel::count() 
{
	return m_count;
}

std::vector<Vector> AbstractModel::genNormals()
{
	return std::vector<Vector>();
}
