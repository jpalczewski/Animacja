#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <thread>
#include <iostream>

#include "ShaderCompiler.h"
#include "JPGLHelper.h"
#include "KeyboardManager.h"
#include "MatrixWrapper.h"
#include "Ground.h"
#include "TextureWrapper.h"
#include "Camera.h"

const int HEIGHT = 800;
const int WIDTH = 600;

KeyboardManager keyboardManager;
GLfloat JPGLHelper::deltaTime = 0.0f;
GLfloat JPGLHelper::lastTime = 0.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	try
	{
		GLfloat currentFrame;

		GLFWwindow *window = JPGLHelper::InitEverything(HEIGHT, WIDTH);
		glfwSetKeyCallback(window, keyCallback);
		
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("glewInit() failed");

		ShaderCompiler shaderGround("ground.vert", "ground.frag");
		

		MatrixWrapper	model(shaderGround.GetProgramID(), "model"),
						projection(shaderGround.GetProgramID(), "projection");

		model.mat4	= glm::rotate(model.mat4, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		projection.mat4 = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		Camera camera(90.0f, 180.0f, 0.0f, 360.0f, 5.0f, shaderGround.GetProgramID(), 25.0f);
		camera.UpdateTargetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		model.mat4 = glm::scale(model.mat4, glm::vec3(10.0f, 10.0f, 0.0f));

		Ground ground(shaderGround.GetProgramID(), 8);

		TextureWrapper groundTexture(GL_TEXTURE0, shaderGround.GetProgramID(), "ground.png", "Texture0");

		keyboardManager.RegisterKey(GLFW_KEY_ESCAPE, std::bind(glfwSetWindowShouldClose, window, GL_TRUE));
		keyboardManager.RegisterKey(GLFW_KEY_H, std::bind(&Camera::YawDown, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_J, std::bind(&Camera::PitchDown, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_K, std::bind(&Camera::PitchUp, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_L, std::bind(&Camera::YawUp, std::ref(camera)));

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);

		while (!glfwWindowShouldClose(window))
		{
			currentFrame = glfwGetTime();
			JPGLHelper::deltaTime = currentFrame - JPGLHelper::lastTime;
			JPGLHelper::lastTime = currentFrame;

			glfwPollEvents();
			keyboardManager.ProcessKeys();
			
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			groundTexture.SendToGPU();

			shaderGround.Execute();

			camera.SendUpdatedMatrix();
			projection.SendToGPU();

			ground.Draw(model);

			glfwSwapBuffers(window);
		}

	
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
	}

	glfwTerminate();
	return 0;
}



void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		keyboardManager.keys[key] = true;
	else if (action == GLFW_RELEASE)
		keyboardManager.keys[key] = false;
	

}