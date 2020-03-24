#include "Actor.h"

Actor::Actor(class Shader* aShader, class VertexArray* aVertexArray)
{
	this->mShader = aShader;
	this->mVertexArray = aVertexArray;
}

void Actor::Draw()
{
	this->mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}
