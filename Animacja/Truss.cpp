#include "Truss.h"


static  inline void addVertex(std::vector<GLfloat> & where, GLfloat x, GLfloat y, GLfloat z, GLfloat normalX, GLfloat normalY, GLfloat normalZ, GLfloat colorR, GLfloat colorG, GLfloat colorB)
{
	where.push_back(x);
	where.push_back(y);
	where.push_back(z);
	where.push_back(normalX);
	where.push_back(normalY);
	where.push_back(normalZ);
	where.push_back(colorR);
	where.push_back(colorG);
	where.push_back(colorB);

}

Truss::Truss(GLuint _shaderID)
{
	GLuint posAttrib, colorsAttrib, floatsPerVertex = 9;

	addVertex(vertices, 5.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	addVertex(vertices, 5.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	addVertex(vertices, 5.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	addVertex(vertices, 5.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);


	addVertex(vertices, -5.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	addVertex(vertices, -5.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	addVertex(vertices, -5.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	addVertex(vertices, -5.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	indexes = { 0, 1, 2};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(GLuint), &(indexes[0]), GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(_shaderID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(posAttrib);

	colorsAttrib = glGetAttribLocation(_shaderID, "color");
	glVertexAttribPointer(colorsAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colorsAttrib);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Truss::Draw(MatrixWrapper& mw)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		mw.SendToGPU();
		glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Truss::~Truss()
{
}
