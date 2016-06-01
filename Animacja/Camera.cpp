#include "Camera.h"




Camera::Camera(GLfloat _minPitch, GLfloat _maxPitch, GLfloat _minYaw, GLfloat _maxYaw, GLfloat _distance, GLuint shaderID, GLfloat _step) : minPitch(_minPitch), maxPitch(_maxPitch), minYaw(_minYaw), maxYaw(_maxYaw), distance(_distance), view(shaderID, "view"), step(_step)
{
	yaw = (minYaw + maxYaw) / 2;
	pitch = (maxPitch + minPitch) / 2;
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::YawUp()
{
	yaw += step * JPGLHelper::deltaTime;
	//if (yaw > maxYaw)
	//	yaw = maxYaw;
}

void Camera::YawDown()
{
	yaw -= step * JPGLHelper::deltaTime;
	//if (yaw < minYaw)
	//	yaw = minYaw;
}

void Camera::PitchUp()
{
	pitch += step * JPGLHelper::deltaTime;
	if (pitch > maxPitch)
		pitch = maxPitch;

}

void Camera::PitchDown()
{
	pitch -= step * JPGLHelper::deltaTime;
	if (pitch < minPitch)
		pitch = minPitch;
}

void Camera::UpdateShader(GLuint _shaderID)
{
	view.SetShader(_shaderID);
}

void Camera::UpdateTargetPosition(glm::vec3 & targetPos)
{
	target = targetPos;
}

void Camera::SendUpdatedMatrix()
{
	cameraPosition.x = glm::cos(glm::radians(yaw))*distance + target.x;
	cameraPosition.y = glm::sin(glm::radians(pitch))*distance + target.y;
	cameraPosition.z = glm::sin(glm::radians(yaw))*distance + target.z;

	view.mat4 = glm::lookAt(cameraPosition, target, cameraUp);
	view.SendToGPU();

	std::cout << "\ryaw:" << yaw << "\tpitch:" << pitch << "\tup: " << cameraUp.y;
}
