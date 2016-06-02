#pragma once
#define GLEW_STATIC
#include <vector>
#include <GL/glew.h>
#include "MatrixWrapper.h"
#include "TrainWall.h"


class Train
{
	enum Side {FRONT=0, BACK, TOP, BOTTOM, LEFT, RIGHT};

	GLuint shaderID;

	std::vector<TrainWall> walls;
	std::vector<glm::mat4> models;

	glm::mat4 finalModel;

	glm::vec3 location;
	GLfloat speedAngle;
public:
	Train(GLuint _shaderID);
	~Train();

	void Draw();

	glm::vec3 & GetLocation() { return location; }

	void Go();
	void Back();
	void DoPhysics();
};

