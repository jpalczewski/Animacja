#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "JPGLHelper.h"
#include "MatrixWrapper.h"
class Light
{
	glm::vec3 minBackgroundColor;
	glm::vec3 maxBackgroundColor;

	glm::vec3 nowBackgroundColor;
	glm::vec3 lightPosition;
	GLfloat ambientLevel;
	GLfloat diffuseLevel;
public:
	Light();
	~Light();

	void AmbientUp();
	void AmbientDown();
	void DiffuseUp();
	void DiffuseDown();

	GLfloat InterpolateR();
	GLfloat InterpolateG();
	GLfloat InterpolateB();


	void UpdateLight(GLuint _shaderID, glm::vec3  & cameraPos);

	void RecalculateBackgroundColor();
};

