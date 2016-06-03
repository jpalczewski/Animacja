#pragma once
#define GLEW_STATIC
#include <vector>
#include <GL/glew.h>
#include "MatrixWrapper.h"

#include "TrainWall.h"
#include "Wheel.h"
#include "Truss.h"

class Train
{
	const int MODEL_WHEEL_OFFSET = 6;
	const int MODEL_TRUSS_OFFSET = 10;
	enum Side {FRONT=0, BACK, TOP, BOTTOM, LEFT, RIGHT};
	enum WheelNum { FRONT_LEFT=0, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT};
	enum TrussNum {TLEFT=0, TRIGHT};
	GLuint shaderID;

	std::vector<TrainWall> walls;
	std::vector<Wheel> wheels;
	std::vector<Truss> truss;

	std::vector<glm::mat4> models;

	glm::mat4 finalModel;

	glm::vec3 location;
	GLfloat speedAngle;
	GLfloat rotation;
public:
	Train(GLuint _shaderID);
	~Train();

	void Draw();

	glm::vec3 & GetLocation() { return location; }

	void Go();
	void Back();
	void DoPhysics();
};

