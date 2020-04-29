#pragma once
#include<GL/glew.h>

class VertexArray
{
public:
	VertexArray(float* verts, int NumVerts, int* AttrArray,
		int* indices, int numIndices);
	~VertexArray();
	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};