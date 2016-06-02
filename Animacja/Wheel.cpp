#include "Wheel.h"
#include <glm/gtx/transform.hpp>
#include "MatrixWrapper.h"


static  inline void addVertex(std::vector<GLfloat> & where, GLfloat x, GLfloat y, GLfloat z, GLfloat normalX, GLfloat normalY, GLfloat normalZ, GLfloat colorR, GLfloat colorG, GLfloat colorB)
{
	std::vector<GLfloat>::iterator it;
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

Wheel::Wheel(int _vertices, int _shaderID) : verticesCount(_vertices)
{
	int offset;
	GLfloat stepInAngle = 360.0f / static_cast<GLfloat>(_vertices);
	GLuint floatsPerVertex = 9;
	GLuint posAttrib, colorsAttrib;

	importantPoints.resize(IMPORTANT_ELEMENT_COUNT);
	
	vertices.reserve(2*(_vertices+1)*floatsPerVertex);
	indexes.reserve(2 * (_vertices + 1)*floatsPerVertex);
	

	for (offset = 0; offset <= _vertices; ++offset)
	{
	 addVertex(vertices, 
		 rLength*glm::sin(glm::radians(offset*stepInAngle)), 
		 rLength*glm::cos(glm::radians(offset*stepInAngle)), 
		 -zOffset, 0.0f, 0.0f, 1.0f, 
		 1-glm::sin(2 * glm::pi<GLfloat>()* offset / _vertices), glm::cos(2 * glm::pi<GLfloat>()* offset / _vertices), offset / _vertices);
	}

	importantPoints[RIGHT] = vertices.end()--;

	for (offset = 0; offset <= _vertices; ++offset)
	{
		addVertex(vertices,
			rLength*glm::sin(glm::radians(-offset*stepInAngle)),
			rLength*glm::cos(glm::radians(-offset*stepInAngle)),
			zOffset, 0.0f, 0.0f, 1.0f, 
			glm::sin(2 * glm::pi<GLfloat>()* offset / _vertices), 1-glm::cos(2 * glm::pi<GLfloat>()* offset / _vertices), offset / _vertices);
	}

	//++importantPoints[RIGHT];
	//importantPoints[LEFT] = vertices.begin();

	for (offset = 0; offset < 2*_vertices + 2; ++offset)
		indexes.push_back(offset);

	for (offset = 0; offset <=  _vertices ; ++offset)
	{
		indexes.push_back((offset));
		indexes.push_back(2*_vertices+1   - offset);
	}
	indexes.push_back((offset));
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &(vertices[0]), GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(_shaderID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(posAttrib);

	colorsAttrib = glGetAttribLocation(_shaderID, "color");
	glVertexAttribPointer(colorsAttrib, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colorsAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Wheel::~Wheel()
{


}

void Wheel::Draw(MatrixWrapper & model)
{
	model.SendToGPU();

	glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()*sizeof(GLfloat));
		glDrawElements(GL_TRIANGLE_FAN, verticesCount + 1, GL_UNSIGNED_INT, &indexes[0]);
		glDrawElements(GL_TRIANGLE_FAN, verticesCount + 1, GL_UNSIGNED_INT, &indexes[verticesCount+1]);
		glDrawElements(GL_TRIANGLE_STRIP, 2 * verticesCount + 2, GL_UNSIGNED_INT, &indexes[2 * verticesCount + 2]);
	glBindVertexArray(0);
}
