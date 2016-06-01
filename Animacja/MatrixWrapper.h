#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderCompiler.h"

class MatrixWrapper
{
	GLuint			locationInGPU;
	const char* name;

public:
	glm::mat4 mat4;
	
	MatrixWrapper() {};
	MatrixWrapper(GLuint _shaderID, const char* nameInGPU);
	~MatrixWrapper();
	

	void SetShader(GLuint _shaderID);
	void SendToGPU();
};

