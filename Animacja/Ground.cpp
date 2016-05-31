#include "Ground.h"

static GLfloat rectangle[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
};

Ground::Ground(GLuint _shaderID, int multiply)
{
	GLint texAttrib, posAttrib;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*_countof(rectangle), rectangle, GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(_shaderID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(posAttrib);

	texAttrib = glGetAttribLocation(_shaderID, "texCoord");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(texAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Ground::~Ground()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void Ground::Draw(MatrixWrapper & model)
{
	glBindVertexArray(VAO);

	model.SendToGPU();

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)_countof(rectangle));

	glBindVertexArray(0);
}