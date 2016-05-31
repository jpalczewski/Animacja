#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <iostream>
#include <SOIL.h>

class JPGLHelper {
public:
	static GLfloat lastTime;
	static GLfloat deltaTime;


	static GLFWwindow* InitEverything(int height, int width);

	static GLuint LoadTexture(const char* filename)
	{
		int width, height;
		unsigned char* image;
		GLuint texture;

		image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
		if(image == nullptr)
			throw std::runtime_error(std::string("JPGLHelper::LoadTexture failed at SOIL_load_image") + std::string(SOIL_last_result()));
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,0, GL_RGB,width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}
};
