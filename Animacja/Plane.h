#pragma once
#define GLEW_STATIC	
#include <GL/glew.h>
#include <vector>

#include "MatrixWrapper.h"

class Plane
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint verticesPerSide;
	std::vector <GLfloat> vertices;
	std::vector <GLuint> indexes;
public:
	Plane(GLuint _shaderID, GLuint _verticesPerSide);
	~Plane();

	void Draw(MatrixWrapper & model);
};