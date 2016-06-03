#include "Train.h"
#include "JPGLHelper.h"
#include <glm/gtx/transform.hpp>
#include "KeyboardManager.h"

extern KeyboardManager keyboardManager;

Train::Train(GLuint _shaderID) : shaderID(_shaderID)
{
	location = glm::vec3(0.0f,9.0f, 0.0f);

	walls.resize(6);
	models.resize(6 + 4 + 2);
	wheels.resize(4);
	truss.resize(2);

	for (int i = 0; i < 6; i++)
		walls[i] = TrainWall(_shaderID, 16);
	
	for (int i = 0; i < 4; ++i)
		wheels[i] = Wheel(256, _shaderID);

	for (int i = 0; i < 2; ++i)
		truss[i] = Truss(_shaderID);

	models[FRONT] = glm::translate(models[FRONT], glm::vec3(0.0f, 0.0f, 5.0f));

	models[BACK] = glm::rotate(models[BACK], glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	models[BACK] = glm::translate(models[BACK], glm::vec3(0.0f, 0.0f, 5.0f));

	models[TOP] = glm::rotate(models[TOP], glm::radians(-90.0f), glm::vec3(1.0f, 0, 0));
	models[TOP] = glm::translate(models[TOP], glm::vec3(0.0f, 0.0f, 5.0f));

	models[LEFT] = glm::rotate(models[LEFT], glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	models[LEFT] = glm::translate(models[LEFT], glm::vec3(0.0f, 0.0f, 5.0f));

	models[RIGHT] = glm::rotate(models[RIGHT], glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	models[RIGHT] = glm::translate(models[RIGHT], glm::vec3(0.0f, 0.0f, 5.0f));
	
	models[BOTTOM] = glm::rotate(models[BOTTOM], glm::radians(90.0f), glm::vec3(1.0f, 0, 0));
	models[BOTTOM] = glm::translate(models[BOTTOM], glm::vec3(0.0f, 0.0f, 5.0f));

	models[MODEL_WHEEL_OFFSET + FRONT_LEFT] = translate(models[MODEL_WHEEL_OFFSET + FRONT_LEFT],glm::vec3(5.0f, -5.0f, 5.5f));
	models[MODEL_WHEEL_OFFSET + FRONT_RIGHT] = translate(models[MODEL_WHEEL_OFFSET + FRONT_RIGHT], glm::vec3(5.0f, -5.0f, -5.5f));

	models[MODEL_WHEEL_OFFSET + BACK_LEFT] = translate(models[MODEL_WHEEL_OFFSET + BACK_LEFT], glm::vec3(-5.0f, -5.0f, 5.5f));
	models[MODEL_WHEEL_OFFSET + BACK_RIGHT] = translate(models[MODEL_WHEEL_OFFSET + BACK_RIGHT], glm::vec3(-5.0f, -5.0f, -5.5f));

	models[MODEL_TRUSS_OFFSET + TLEFT] = glm::translate(models[MODEL_TRUSS_OFFSET + TLEFT], glm::vec3(0.0f, -5.0f, -6.5f));
	models[MODEL_TRUSS_OFFSET + TRIGHT] = glm::translate(models[MODEL_TRUSS_OFFSET + TRIGHT], glm::vec3(0.0f, -5.0f, 6.5f));

}

Train::~Train()
{
}

void Train::Draw()
{
	MatrixWrapper model(shaderID, "model");


	for (int i = 0; i < 12; ++i)
	{
		model.mat4 = glm::mat4();
		model.mat4 = glm::translate(model.mat4, location);
		model.mat4 *= models[i];
		if (i < 6)
			walls[i].Draw(model);
		else if (i < 10)
		{
			model.mat4 = glm::rotate(model.mat4, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			wheels[i - 6].Draw(model);
		}
		else
		{
			model.mat4 = glm::translate(model.mat4, 
				glm::vec3(
				glm::cos(glm::radians(rotation))*3.0f,
				glm::sin(glm::radians(rotation))*3.0f,
				0.0f
							)
				);
			truss[i - 10].Draw(model);
		}
	}



}

void Train::Go()
{
	speedAngle += 15 * JPGLHelper::deltaTime;
	rotation -= speedAngle;

	if (speedAngle > 90.0f)
		speedAngle = 90.0f;

	if (rotation >= 360.f)
		rotation -= 360.0f;
}

void Train::Back()
{


	speedAngle -= 15 * JPGLHelper::deltaTime;
	rotation -= speedAngle;

	if (speedAngle < -90.0f)
		speedAngle = -90.0f;

	if (rotation >= 360.f)
		rotation -= 360.0f;
}

void Train::DoPhysics()
{
	const GLfloat step = 300;
	location.x += step*glm::sin(glm::radians(speedAngle))*JPGLHelper::deltaTime;

	if (!keyboardManager.keys[GLFW_KEY_A] && !keyboardManager.keys[GLFW_KEY_Z])
	if (glm::abs(speedAngle) > 0.0000005)
	{
		speedAngle -= speedAngle  * JPGLHelper::deltaTime;
		rotation -= (rotation)*speedAngle*JPGLHelper::deltaTime;
	}
}
