#version 330 core

in vec3 inPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	gl_Position = vec4(inPosition, 1.0) * uModel * uView * uProjection;
}