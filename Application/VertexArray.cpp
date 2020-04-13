#include "pch.h"
#include "VertexArray.h"


VertexArray::VertexArray(float *vertexBuffer, unsigned int vertexBufferSize, unsigned int *IndexBuffer, unsigned int numOfIndices):
	mVertexBufferSize(vertexBufferSize),
	mIndexBufferSize(numOfIndices)
{
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * 8 * sizeof(float), vertexBuffer, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(float), IndexBuffer, GL_STATIC_DRAW);

	// Position attribute
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , 0);

	// Normal attribute
	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 3)); 

	// UV Coordinates
	glEnableVertexAttribArray(2); 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 6)); 
}


void VertexArray::Bind() 
{
	glBindVertexArray(mVertexArray);
}

VertexArray::~VertexArray()
{
}
