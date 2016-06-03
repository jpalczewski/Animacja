#include "Light.h"


Light::Light()
{
	ambientLevel = 1.0f;
	diffuseLevel = 1.0f;
	lightPosition = glm::vec3(0.0f, 40.0f, 0.0f);

	minBackgroundColor = glm::vec3(0.0f, 0.0f, 0.15f);
	maxBackgroundColor = glm::vec3(0.0f, 0.5f, 1.0f);
	RecalculateBackgroundColor();
}


Light::~Light()
{
}

void Light::AmbientUp()
{
	ambientLevel += 1.0f * JPGLHelper::deltaTime;
	if (ambientLevel > 1.0f)
		ambientLevel = 1.0f;
	RecalculateBackgroundColor();
}

void Light::AmbientDown()
{
	ambientLevel -= 1.0f * JPGLHelper::deltaTime;
	if (ambientLevel < 0)
		ambientLevel = 0;
	RecalculateBackgroundColor();
}

void Light::DiffuseUp()
{
	diffuseLevel += 1.0f * JPGLHelper::deltaTime;
	if (diffuseLevel > 1.0f)
		diffuseLevel = 1.0f;
}

void Light::DiffuseDown()
{
	diffuseLevel -= 1.0f * JPGLHelper::deltaTime;
	if (diffuseLevel < 0)
		diffuseLevel = 0.0f;
}

GLfloat Light::InterpolateR()
{
	return nowBackgroundColor.r;
}

GLfloat Light::InterpolateG()
{
	return nowBackgroundColor.g;
}

GLfloat Light::InterpolateB()
{
	return nowBackgroundColor.b;
}

void Light::UpdateLight(GLuint _shaderID, glm::vec3  & cameraPos)
{
	glUniform3f(glGetUniformLocation(_shaderID, "light.position"), lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(glGetUniformLocation(_shaderID, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(_shaderID, "light.ambient"), ambientLevel / 2, ambientLevel / 2, ambientLevel / 2);
	glUniform3f(glGetUniformLocation(_shaderID, "light.diffuse"), diffuseLevel / 2, diffuseLevel / 2, diffuseLevel / 2);
	glUniform3f(glGetUniformLocation(_shaderID, "light.specular"), diffuseLevel , diffuseLevel , diffuseLevel );
	glUniform1f(glGetUniformLocation(_shaderID, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(_shaderID, "light.linear"), 0.0014f);
	glUniform1f(glGetUniformLocation(_shaderID, "light.quadratic"), 0.000007f);

}

void Light::RecalculateBackgroundColor()
{
	nowBackgroundColor.r = minBackgroundColor.r + ambientLevel*(maxBackgroundColor.r - minBackgroundColor.r);
	nowBackgroundColor.g = minBackgroundColor.g + ambientLevel*(maxBackgroundColor.g - minBackgroundColor.g);
	nowBackgroundColor.b = minBackgroundColor.b + ambientLevel*(maxBackgroundColor.b - minBackgroundColor.b);
}
