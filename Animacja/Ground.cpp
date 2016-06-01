#include "Ground.h"
#include <algorithm>
#include <functional>
#include <array>
static GLfloat rectangle[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
};

using namespace std::placeholders;

Ground::Ground(GLuint _shaderID, int _multiply) : multiply(_multiply), VBOs(_multiply, 0), vertices(multiply)
{
	shaderID = _shaderID;
	GLint texAttrib, posAttrib;
	int flipper = 0;
	std::array<GLfloat, 4> texCoord_x = { 0.0f, 1.0f, 0.0f, 1.0f };
	std::array<GLfloat, 4> texCoord_y = { 1.0f, 1.0f, 0.0f, 0.0f };

	//std::for_each(vertices.begin(), vertices.end(), std::bind(&std::vector < std::vector<GLfloat> >::reserve, _1, 2*5*(multiply+1)));
	for (int i = 0; i < multiply; ++i)
		vertices[i].reserve(multiply);
	


	for (int i = 0; i < multiply; ++i)
		for (int j = 0; j <= multiply; ++j)
		{
			vertices[i].push_back(0.5f - static_cast<GLfloat>(i)/multiply);
			vertices[i].push_back(0.5f - static_cast<GLfloat>(j) / multiply);
			vertices[i].push_back(0.0f);
			vertices[i].push_back(texCoord_x[flipper]);
			vertices[i].push_back(texCoord_y[flipper]);

			vertices[i].push_back(0.5f - static_cast<GLfloat>(i + 1) / multiply);
			vertices[i].push_back(0.5f - static_cast<GLfloat>(j) / multiply);
			vertices[i].push_back(0.0f);
			vertices[i].push_back(texCoord_x[flipper+1]);
			vertices[i].push_back(texCoord_y[flipper+1]);

			flipper += 2;
			flipper %= 4;
		}


	glGenVertexArrays(1, &VAO);
	//std::for_each(VBOs.begin(), VBOs.end(), [&](std::vector<GLuint>::iterator it){glGenBuffers(1, &(*it)); });
	
	for (int i = 0; i < multiply; ++i)
	{
		glGenBuffers(1, &VBOs[i]);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices[i].size(), &vertices[i][0], GL_STATIC_DRAW);

		posAttrib = glGetAttribLocation(_shaderID, "position");
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(posAttrib);

		texAttrib = glGetAttribLocation(_shaderID, "texCoord");
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(texAttrib);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}


Ground::~Ground()
{
	glDeleteVertexArrays(1, &VAO);
	for (int i = 0; i < multiply; ++i)
		glDeleteBuffers(1, &VBOs[i]);
	
}


void Ground::Draw(MatrixWrapper & model)
{
	GLint texAttrib, posAttrib;

	glBindVertexArray(VAO);

	model.SendToGPU();

	for (int i = 0; i < multiply; ++i)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		posAttrib = glGetAttribLocation(_shaderID, "position");
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(posAttrib);

		texAttrib = glGetAttribLocation(_shaderID, "texCoord");
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(texAttrib);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLuint)vertices[i].size());
	}
	glBindVertexArray(0);
}