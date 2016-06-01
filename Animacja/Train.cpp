#include "Train.h"
#include <glm/gtx/transform.hpp>

Train::Train(GLuint _shaderID) : shaderID(_shaderID)
{
	location = glm::vec3(0.0f, 15.0f, 0.0f);

	walls.resize(6);
	models.resize(6);

	for (int i = 0; i < 6; i++)
		walls[i] = TrainWall(_shaderID, 16);
	
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
}

Train::~Train()
{
}

void Train::Draw()
{
	MatrixWrapper model(shaderID, "model");

	/*model.mat4 = models[FRONT];
	walls[FRONT].Draw(model);

	model.mat4 = models[BACK];
	walls[BACK].Draw(model);

	model.mat4 = models[TOP];
	walls[TOP].Draw(model);

	model.mat4 = models[LEFT];
	walls[LEFT].Draw(model);

	model.mat4 = models[RIGHT];
	walls[RIGHT].Draw(model);*/

	for (int i = 0; i < 6; ++i)
	{
		model.mat4 = models[i];
	//	model.mat4 = glm::translate(model.mat4, location);
		walls[i].Draw(model);
	}

}
