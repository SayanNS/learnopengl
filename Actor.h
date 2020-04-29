#pragma once
#include "Shader.h"
#include "VertexArray.h"

class Actor
{
public:
	Actor(class Game* game);

private:
	
	class Shader* mShader;
	class VertexArray* mVertexArray;
};
