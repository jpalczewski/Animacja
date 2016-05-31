#include <fstream>
#include <string>
#include <cerrno>
#include <exception>

#include "ShaderCompiler.h"

std::string _ReadFile(const GLchar* path)
{
	std::string contents;
	std::ifstream	in(path, std::ios::in);
	if(in)
	{
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	}
	else
		throw std::runtime_error("ShaderCompiler::_ReadFile failed with " + errno);

	return contents;
}

GLuint _CompileShader(const GLchar * shaderCode, GLenum shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);
	GLint success;

	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(success != GL_TRUE)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
		std::string msg = std::string("Shader compilation failed: ") + infoLog;
		throw std::runtime_error(msg.c_str());
	}

	return shaderID;
}

ShaderCompiler::ShaderCompiler(const GLchar * vertexPath, const GLchar* fragmentPath)
{
	GLint result;

	std::string 	vertexShaderSrc = 		_ReadFile(vertexPath),
					fragmentShaderSrc = 	_ReadFile(fragmentPath);

	GLuint			vertexShaderID	= 			_CompileShader(vertexShaderSrc.c_str(), GL_VERTEX_SHADER),
					fragmentShaderID =			_CompileShader(fragmentShaderSrc.c_str(), GL_FRAGMENT_SHADER);

	_programID = glCreateProgram();
	glAttachShader(_programID, vertexShaderID);
	glAttachShader(_programID, fragmentShaderID);
	glLinkProgram(_programID);

	// Print linking errors if any

	glGetProgramiv(_programID, GL_LINK_STATUS, &result);
	if (!result)
	{
			GLchar infoLog[512];
			glGetProgramInfoLog(_programID, sizeof(infoLog), NULL, infoLog);
			std::string msg = std::string("Shader program linking: ") + infoLog;
			throw std::runtime_error(msg.c_str());
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
