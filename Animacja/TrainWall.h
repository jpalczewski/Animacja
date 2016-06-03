#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

#include "MatrixWrapper.h"
class TrainWall
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint verticesPerSide;
	std::vector <GLfloat> vertices;
	std::vector <GLuint> indexes;
public:
	TrainWall() {};
	TrainWall(GLuint _shaderID, GLuint _verticesPerSide);
	~TrainWall();

	void Draw(MatrixWrapper &model)
	{
		glBindVertexArray(VAO);

		model.SendToGPU();

		//	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLuint)_countof(rectangle));
		glDrawElements(GL_TRIANGLE_STRIP, indexes.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
};

