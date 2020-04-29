#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	vec4 pos = vec4(aPos, 1.0);
	gl_Position = pos * uView * uProjection;
	FragPos = aPos;
	Normal = aNormal;
}