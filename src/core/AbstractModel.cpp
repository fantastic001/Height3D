
#include "AbstractModel.hpp"

using namespace std;

void AbstractModel::send(Buffer* vertexBuffer, Buffer* indexBuffer, Buffer* colorBuffer, Buffer* textureBuffer, Buffer* normalsBuffer) 
{
	vector<float> 
	vertices = genVertices(), 
	colors = genVertexColors(), 
	coords = genTextureCoordinates(); 
	vector<float> normals = genNormals();

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

std::vector<float> AbstractModel::genNormals()
{
	return std::vector<float>();
}

int AbstractModel::countVertices() 
{
	return genVertices().size() / 3;
}

int AbstractModel::countTriangles() 
{
	return genIndices().size() / 3;
}
