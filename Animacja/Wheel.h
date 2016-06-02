#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include "MatrixWrapper.h"

class Wheel
{
	int IMPORTANT_ELEMENT_COUNT = 4;
	
	GLfloat zOffset = 0.5f;
	GLfloat rLength = 4.0f;

	enum Element { LEFT_CENTER = 0, RIGHT_CENTER, LEFT, RIGHT };

	GLuint VAO;
	GLuint VBO;
	GLuint verticesCount;

	std::vector <GLuint> indexes;
	std::vector <GLfloat> vertices;
	
	std::vector<std::vector<GLfloat>::iterator> importantPoints;
	
public:
	Wheel() {};
	Wheel(int vertices, int _shaderID);
	~Wheel();

	void Draw(MatrixWrapper & model);
};

