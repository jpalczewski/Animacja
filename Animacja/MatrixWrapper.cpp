#include "MatrixWrapper.h"


MatrixWrapper::MatrixWrapper(GLuint _shaderID, const char *_name) : name(_name)
{
	SetShader(_shaderID);
}


MatrixWrapper::~MatrixWrapper()
{
}

void MatrixWrapper::SetShader(GLuint _shaderID)
{
	locationInGPU = glGetUniformLocation(_shaderID, name);
}

void MatrixWrapper::SendToGPU()
{
	glUniformMatrix4fv(locationInGPU, 1, GL_FALSE, glm::value_ptr(mat4));
}
