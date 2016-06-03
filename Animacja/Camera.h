#pragma once
#include "JPGLHelper.h"
#include "MatrixWrapper.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
	GLfloat minPitch;
	GLfloat maxPitch;
	GLfloat minYaw;
	GLfloat maxYaw;

	MatrixWrapper view;

	glm::vec3 target;
	glm::vec3 cameraUp;
	GLfloat distance;
	GLfloat yaw;
	GLfloat pitch;

	GLfloat step;

public:
	Camera(GLfloat _minPitch, GLfloat _maxPitch, GLfloat _minYaw, GLfloat _maxYaw, GLfloat distance, GLuint shaderID, GLfloat step);
	~Camera();

	void YawUp();
	void YawDown();
	void PitchUp();
	void PitchDown();
	void DistanceUp();
	void DistanceDown();

	void UpdateShader(GLuint _shaderID);
	void UpdateTargetPosition(glm::vec3 & targetPos);
	void SendUpdatedMatrix();


	glm::vec3 cameraPosition;
};

