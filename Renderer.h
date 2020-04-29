#pragma once
#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();

	bool Initialize(const char* file_name);

	void Draw();

	void SetShaderUniform(const char* name, GLfloat* matrix);

	void SetShaderUniform1(const char* name, GLfloat* matrix);

	void SetShaderActive();

	void SetVertexActive();

private:
	VertexArray* vertexArray;

	Shader* shader;
};

