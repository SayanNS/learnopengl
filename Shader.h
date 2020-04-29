#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const std::string& vertName, const std::string& fragName);
	
	void Unload();

	void SetActive();

	void SetMatrixUniform(const char* name, GLfloat* matrix);

	void SetVec3Uniform(const char* name, GLfloat* vec3);

private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);

	bool IsCompiled(GLuint shader);

	bool IsValidProgram();

	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};

