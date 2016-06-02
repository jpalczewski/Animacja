#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

#include "MatrixWrapper.h"

class Truss
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<GLfloat> vertices;
	std::vector<GLuint>	indexes;
public:

	Truss(GLuint _shaderID);
	void Draw(MatrixWrapper & mw);
	~Truss();
};

