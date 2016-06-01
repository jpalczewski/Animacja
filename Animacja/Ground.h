#pragma once
#define GLEW_STATIC	
#include <GL/glew.h>
#include <vector>

#include "MatrixWrapper.h"

class Ground
{
	GLuint shaderID;
	int multiply;
	GLuint VAO;
	std::vector<GLuint> VBOs;
	std::vector < std::vector<GLfloat> > vertices;
public:
	Ground(GLuint _shaderID, int multiply);
	~Ground();

	void Draw(MatrixWrapper & model);
};

