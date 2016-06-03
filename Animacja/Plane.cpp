#include "Plane.h"
#include <array>
#include <glm/gtx/transform.hpp>

static GLfloat rectangle[] = {
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
};

Plane::Plane(GLuint _shaderID, GLuint _verticesPerSide) : verticesPerSide(_verticesPerSide), shaderID(_shaderID)
{
	std::array<GLfloat, 2> texCoord_x = { 0.0f, 1.0f };
	std::array<GLfloat, 2> texCoord_y = { 1.0f, 0.0f };

	GLint texAttrib, posAttrib, normalAttrib;
	
	GLuint	xSize = _verticesPerSide,
		ySize = _verticesPerSide,
		floatsPerVertex = 3 + 3 + 2,
		vertexTableSize = xSize*ySize*floatsPerVertex; // 3 for vertex coord + 2 tex coords.
	
	GLfloat minimumPosition = -5.0f;
	GLfloat positionRange = 10.0f;

	GLfloat xPos, yPos, xRatio, yRatio;
	glm::vec3 normal =glm::vec3(0.0f, 0.0f, 1.0f);

	vertices.resize(vertexTableSize, 0.0f);
	
	
	/*for (int i = 1; i < _verticesPerSide*_verticesPerSide; ++i)
	{
	indexes.push_back(i);
		if ((i - 1) % _verticesPerSide == 0 && i != 1)
			indexes.push_back(i);
		indexes.push_back(i + _verticesPerSide);
		if ((i + _verticesPerSide) % _verticesPerSide == 0)
			indexes.push_back(i + _verticesPerSide);
			

	}
	*/
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

			vertices[offset++] = xPos;
			vertices[offset++] = yPos;
			vertices[offset++] = 0.0;
			vertices[offset++] = normal.x;
			vertices[offset++] = normal.y;
			vertices[offset++] = normal.z;
			vertices[offset++] = texCoord_x[x%2];
			vertices[offset++] = texCoord_y[y%2];

		}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(GLuint), &(indexes[0]), GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(_shaderID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(posAttrib);

	texAttrib = glGetAttribLocation(_shaderID, "texCoord");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(texAttrib);

	normalAttrib = glGetAttribLocation(_shaderID, "normal");
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(normalAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Plane::~Plane()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Plane::Draw(MatrixWrapper & model)
{
	//MatrixWrapper modelNormal(shaderID, "modelNormal");

	glm::mat3 modelToSend;
	glm::mat4 modelNormal = model.mat4;
	modelNormal = glm::inverse(modelNormal);
	modelNormal = glm::transpose(modelNormal);
	
	modelToSend = glm::mat3(modelNormal);

	glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), 32.0f);
	glUniform1i(glGetUniformLocation(shaderID, "material.texture"), 0);

	glBindVertexArray(VAO);

	model.SendToGPU();
	glUniformMatrix3fv(glGetUniformLocation(shaderID, "modelNormal"), 1, GL_FALSE, glm::value_ptr(modelToSend));

	glDrawElements(GL_TRIANGLE_STRIP, indexes.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}