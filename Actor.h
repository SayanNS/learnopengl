#pragma once
#include "Shader.h"
#include "VertexArray.h"

class Actor
{
public:
	Actor(class Shader*, class VertexArray*);
	void Draw();
private:
	
	class Shader* mShader;
	class VertexArray* mVertexArray;
};
