
#include "common.hpp"
#include "Buffer.hpp"

using namespace std; 

Buffer::Buffer(GLenum _type) 
{
	type = _type;
	glGenBuffers(1, &id);
}

void Buffer::bind() 
{
	glBindBuffer(type, id);
}

void Buffer::sendData(std::vector<float> data) 
{
	sendData(&data[0], data.size());
}

void Buffer::sendData(std::vector<int> data) 
{
	sendData(&data[0], data.size());
}
void Buffer::sendData(Vector* data, int n, bool include_w) 
{
	vector<float> vdata;
	for (int i = 0; i<n; i++) {
		vdata.push_back(data[i].getX());
		vdata.push_back(data[i].getY());
		vdata.push_back(data[i].getZ());
		if (include_w) vdata.push_back(data[i].getW());
	}
	sendData(vdata);
}

void Buffer::sendData(std::vector<Vector> data, bool include_w) 
{
	sendData(&data[0], data.size(), include_w);
}

void Buffer::sendData(float* data, int n) 
{
	bind();
	glBufferData(type, n * sizeof(float), data, GL_STATIC_DRAW);
}

void Buffer::sendData(int* data, int n) 
{
	bind();
	glBufferData(type, n * sizeof(int), data, GL_STATIC_DRAW);
}
