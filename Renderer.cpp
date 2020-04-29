#include "Renderer.h"
#include "ParseJson.h"

Renderer::Renderer()
{
	shader = nullptr;
	vertexArray = nullptr;
}

bool Renderer::Initialize(const char* file_name)
{
	renderdata::Data data;
	
	if (!renderdata::ParseJsonFile(file_name, &data))
	{
		return false;
	}

	shader = new Shader();

	if (!shader->Load(data.vert_shader_name, data.frag_shader_name))
	{
		return false;
	}

	vertexArray = new VertexArray(data.vertices_array, data.vertices_num, data.attr_array, data.indices_array, data.indices_num);

	return true;
}

void Renderer::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::SetShaderUniform(const char* name, GLfloat* matrix)
{
	this->shader->SetMatrixUniform(name, matrix);
}

void Renderer::SetShaderUniform1(const char* name, GLfloat* matrix)
{
	this->shader->SetVec3Uniform(name, matrix);
}

void Renderer::SetShaderActive()
{
	this->shader->SetActive();
}

void Renderer::SetVertexActive()
{
	this->vertexArray->SetActive();
}
