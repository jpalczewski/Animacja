#include "JPGLHelper.h"


GLFWwindow* JPGLHelper::InitEverything(int width, int height)
{
	GLFWwindow* window = nullptr;
	try
	{
			if(glfwInit()!=GL_TRUE)
			{
				std::cerr << "glfwInit() failed";
				throw std::runtime_error("glfwInit() failed");
			}

		    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		    glfwWindowHint(GLFW_DEPTH_BITS, 32);
			glfwWindowHint(GLFW_SAMPLES, 16);
		    window = glfwCreateWindow( width,height, "openGL", nullptr, nullptr);
		    glfwMakeContextCurrent(window);
		    glfwSwapInterval(1);

		    //Rozwiązanie wskazane dla ekranów o wyższym DPI.
		    glfwGetFramebufferSize(window,  &width,&height);
		    glViewport(0,0, width,height);

	}
	catch(std::exception &e)
	{
		std::cerr << "JPGLHelper::InitEverything failed";
	}

	return window;
}
