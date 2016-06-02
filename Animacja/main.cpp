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
#include "Plane.h"
#include "TextureWrapper.h"
#include "Camera.h"

#include "Train.h"
#include "Wheel.h"

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
		ShaderCompiler shaderTrain("train.vert", "train.frag");

		MatrixWrapper	modelPlane(shaderGround.GetProgramID(), "model"),
			modelIdentity(shaderTrain.GetProgramID(), "model"),
						projection(shaderGround.GetProgramID(), "projection");

		modelPlane.mat4	= glm::rotate(modelPlane.mat4, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		projection.mat4 = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 500.0f);

		Camera camera(-180.0f, 180.0f, 0.0f, 360.0f, 5.0f, shaderGround.GetProgramID(), 25.0f);
		
		camera.UpdateTargetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		modelPlane.mat4 = glm::scale(modelPlane.mat4, glm::vec3(10.0f, 10.0f, 0));
		modelIdentity.mat4 = glm::mat4(1.0f);
		
		Plane ground(shaderGround.GetProgramID(),32);
		Train train(shaderTrain.GetProgramID());
			
		TextureWrapper groundTexture(GL_TEXTURE0, shaderGround.GetProgramID(), "ground.png", "Texture0");

		keyboardManager.RegisterKey(GLFW_KEY_ESCAPE, std::bind(glfwSetWindowShouldClose, window, GL_TRUE));
		keyboardManager.RegisterKey(GLFW_KEY_H, std::bind(&Camera::YawDown, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_J, std::bind(&Camera::PitchDown, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_K, std::bind(&Camera::PitchUp, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_L, std::bind(&Camera::YawUp, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_U, std::bind(&Camera::DistanceUp, std::ref(camera)));
		keyboardManager.RegisterKey(GLFW_KEY_I, std::bind(&Camera::DistanceDown, std::ref(camera)));

		keyboardManager.RegisterKey(GLFW_KEY_A, std::bind(&Train::Go, std::ref(train)));
		keyboardManager.RegisterKey(GLFW_KEY_Z, std::bind(&Train::Back, std::ref(train)));

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		while (!glfwWindowShouldClose(window))
		{
			currentFrame = glfwGetTime();
			JPGLHelper::deltaTime = currentFrame - JPGLHelper::lastTime;
			JPGLHelper::lastTime = currentFrame;

			glfwPollEvents();
			keyboardManager.ProcessKeys();
			
			camera.UpdateTargetPosition(train.GetLocation());
			train.DoPhysics();

			glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/*
			
				rysowanie p³aszczyzny

			*/

			groundTexture.SendToGPU();

			shaderGround.Execute();

			camera.UpdateShader(shaderGround.GetProgramID());
			camera.SendUpdatedMatrix();
			
			projection.SetShader(shaderGround.GetProgramID());
			projection.SendToGPU();

			ground.Draw(modelPlane);


			/*
			
				rysowanie poci¹gu
			
			*/

			shaderTrain.Execute();
			
			camera.UpdateShader(shaderGround.GetProgramID());
			camera.SendUpdatedMatrix();
			
			projection.SetShader(shaderTrain.GetProgramID());
			projection.SendToGPU();

			
			train.Draw();

			modelIdentity.SendToGPU();

			
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