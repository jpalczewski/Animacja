#pragma once
/*
 * ShaderCompiler.h
 *
 *  Created on: 28 maj 2016
 *      Author: erxyi
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class ShaderCompiler {
	GLuint _programID;

public:
	ShaderCompiler(const GLchar * vertexPath, const GLchar* fragmentPath);

	void Execute() const
	{
		glUseProgram(_programID);
	}

	GLuint GetProgramID() const
	{
		return _programID;
	}
};




