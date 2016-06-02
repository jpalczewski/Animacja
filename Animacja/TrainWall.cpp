#include "TrainWall.h"
#include <array>

TrainWall::TrainWall(GLuint _shaderID, GLuint _verticesPerSide)
{
	GLint colorsAttrib, posAttrib, normalAttrib;

	GLuint	xSize = _verticesPerSide,
		ySize = _verticesPerSide,
		floatsPerVertex = 3 + 3 + 3,
		vertexTableSize = xSize*ySize*floatsPerVertex; 

	GLfloat minimumPosition = -5.0f;
	GLfloat positionRange = 10.0f;

	GLfloat xPos, yPos, xRatio, yRatio;
	glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0)));
	glm::vec3 color;
	vertices.resize(vertexTableSize, 0.0f);

	for (int y = 0; y < ySize - 1; ++y)
	{
		if (y > 0) indexes.push_back(y*ySize);
		for (int x = 0; x < xSize; ++x)
		{
			indexes.push_back(y*ySize + x);
			indexes.push_back((y + 1)*ySize + x);
		}
		if (y < ySize - 2) indexes.push_back((y + 1)*ySize + xSize - 1);
	}

	int offset = 0;
	for (int y = 0; y < ySize; ++y)
		for (int x = 0; x < xSize; ++x)
		{
			xRatio = GLfloat(x) / static_cast<GLfloat>(xSize - 1);
			yRatio = 1.0f - y / static_cast<GLfloat>(ySize - 1);
			//yRatio = y / static_cast<GLfloat>(ySize - 1);

			xPos = minimumPosition + xRatio*positionRange;
			yPos = minimumPosition + yRatio*positionRange;

			color.r = glm::sin(xRatio)*glm::exp(yRatio);
			color.g = glm::tan(xRatio/(yRatio+1));
			color.b = 1 - xRatio*yRatio;

			color = glm::normalize(color);
			

			vertices[offset++] = xPos;
			vertices[offset++] = yPos;
			vertices[offset++] = 0.0;
			vertices[offset++] = normal.x;
			vertices[offset++] = normal.y;
			vertices[offset++] = normal.z;
			vertices[offset++] = color.r;
			vertices[offset++] = color.g;
			vertices[offset++] = color.b;
		}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
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


TrainWall::~TrainWall()
{
}
