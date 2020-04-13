#pragma once
#include <GL/glew.h>
class VertexArray
{
public:
	VertexArray(float *vertexBuffer , unsigned int vertexBufferSize , unsigned int *IndexBuffer , unsigned int numOfIndices);
	~VertexArray();

	void Bind(); 

	unsigned int GetVertexBufferSize() { return mVertexBufferSize;  }
	unsigned int GetIndexBufferSize() { return mIndexBufferSize;  }

private:

	unsigned int mVertexBufferSize; 
	unsigned int mIndexBufferSize; 


	unsigned int mVertexArray; 
	unsigned int mVertexBuffer; 
	unsigned int mIndexBuffer; 
};

