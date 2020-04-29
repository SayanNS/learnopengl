#include "VertexArray.h"

VertexArray::VertexArray(float* verts, int NumVerts, int* AttrArray,
	int* indices, int numIndex)
{
	mNumVerts = NumVerts;
	mNumIndices = numIndex;

	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	glBufferData(
		GL_ARRAY_BUFFER,
		NumVerts * sizeof(float),
		verts,
		GL_STATIC_DRAW
	);

	int current = 0;
	int total = (*AttrArray);

	for (int i = 0; current != total; i++)
	{
		glEnableVertexAttribArray(i);

		int value = AttrArray[i + 1];

		glVertexAttribPointer(
			i,
			value,
			GL_FLOAT,
			GL_FALSE,
			sizeof(float) * total,
			reinterpret_cast<void*>(sizeof(float) * current)
		);

		current += value;
	}
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
