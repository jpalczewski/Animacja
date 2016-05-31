#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <Windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderCompiler.h"
#include "JPGLHelper.h"
const int HEIGHT = 800;
const int WIDTH = 600;


void keyCallback2(GLFWwindow* window, int key, int scancode, int action, int mode);

inline void sendMatToGPU(ShaderCompiler & sc, glm::mat4 & t, const char* name)
{
    GLuint matLocation = glGetUniformLocation(sc.GetProgramID(), name);
    glUniformMatrix4fv(matLocation, 1, GL_FALSE, glm::value_ptr(t));

}

int main2()
{
  glm::mat4 transformMatrix;
  GLfloat rotationAngle = 0.0f;
  GLuint logoPKP;

	GLFWwindow* window = JPGLHelper::InitEverything(HEIGHT,WIDTH);
	glfwSetKeyCallback(window, keyCallback2);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("GLEW Initialization failed");
	ShaderCompiler sc("gl_04.vert", "gl_04.frag");
	try
	{

		logoPKP = JPGLHelper::LoadTexture("pkp2.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
     std::cout << logoPKP << std::endl;

     GLfloat vertices[] = {
             // coordinates          // color
   /*   0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
      -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,*/

    	        // Positions          // Colors           // Texture Coords
    	         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
    	         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
    	        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
    	        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Top Left

              0.5f,  0.5f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Top Right
              0.5f, -0.5f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Bottom Right
             -0.5f, -0.5f, -1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Bottom Left
             -0.5f,  0.5f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Top Left

     };

     GLuint elements[] = {
    		 /* 0,	1,	2,
			    1, 3,  2,*/
    	        0, 1, 3, // First Triangle
    	        1, 2, 3,  // Second Triangle

              4, 5, 7,
              5, 6, 7,

              0,4, 5,
              0, 1 ,5,

              3,7,2,
              2,6,7,

              0,3,7,
              0,4,7,

              1,5,6,
              1,2,6

     };
     glm::vec3 cubePositions[] = {
       glm::vec3( 0.0f,  0.0f,  0.0f),
       glm::vec3( 2.0f,  5.0f, -15.0f),
       glm::vec3(-1.5f, -2.2f, -2.5f),
       glm::vec3(-3.8f, -2.0f, -12.3f),
       glm::vec3( 2.4f, -0.4f, -3.5f),
       glm::vec3(-1.7f,  3.0f, -7.5f),
       glm::vec3( 1.3f, -2.0f, -2.5f),
       glm::vec3( 1.5f,  2.0f, -2.5f),
       glm::vec3( 1.5f,  0.2f, -1.5f),
       glm::vec3(-1.3f,  1.0f, -1.5f)
     };
     GLuint VBO, VAO, EBO;

     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);


     glBindVertexArray(VAO);

     glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	   // vertex geometry data
	 GLint posAttrib = glGetAttribLocation(sc.GetProgramID(), "position");
	 glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	 glEnableVertexAttribArray(posAttrib);

	 GLint colAttrib = glGetAttribLocation(sc.GetProgramID(), "color");
	 glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	 glEnableVertexAttribArray(colAttrib);

	 GLint texAttrib = glGetAttribLocation(sc.GetProgramID(), "texture");
	 glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	 glEnableVertexAttribArray(texAttrib);

	 glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	 glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	 glm::mat4 model, view, projection;
	 model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
   projection = glm::perspective(glm::radians(45.0f), (GLfloat)(WIDTH)/(GLfloat)(HEIGHT), 0.1f, 100.0f);
// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
      glfwPollEvents();

      glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
                              glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                             transformMatrix = glm::rotate(transformMatrix, -glm::radians(rotationAngle), glm::vec3(1.0f,1.0f, 0.0f));

                              rotationAngle += 0.005f;
                              if(rotationAngle >= 360.f)
                            	  rotationAngle -= 360.0f;

                              GLuint transfomMatrixLocation = glGetUniformLocation(sc.GetProgramID(), "transform");
                              glUniformMatrix4fv(transfomMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));

                              sendMatToGPU(sc, view, "viewMat");
                              sendMatToGPU(sc, projection, "projectionMat");
                              sendMatToGPU(sc, model, "modelMat");

                              // Draw our first triangle
                              sc.Execute();

                              glActiveTexture(GL_TEXTURE0);
                              glBindTexture(GL_TEXTURE_2D, logoPKP);
                              glUniform1i(glGetUniformLocation(sc.GetProgramID(), "Texture0"), 0);

                              glBindVertexArray(VAO);
                              for(GLuint i = 0; i < 10; i++)
                              {
                                glm::mat4 model;
                                model = glm::translate(model, cubePositions[i]);
                                GLfloat angle = 20.0f * i;

                                model = glm::rotate(model, angle, glm::vec3(1.0f, 0.2f, 0.1994f));
                                sendMatToGPU(sc, model, "modelMat");
                                glDrawElements(GL_TRIANGLES, std::extent< decltype(elements) >::value, GL_UNSIGNED_INT, 0);
                              }

                              glBindVertexArray(0);

                              // Swap the screen buffers
                              glfwSwapBuffers(window);


    }

    glfwTerminate();
    return 0;
}


void keyCallback2(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
