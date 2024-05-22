#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main()
{
	GLfloat vertices[] = { // vertices coordiants

		 0.5f,  0.5f, 0.0f,  0.8f, 0.3f, 0.02f, // Lower left corner
		 0.5f, -0.5f, 0.0f,  0.8f, 0.3f, 0.02f, // Lower right corner
		-0.5f, -0.5f, 0.0f,  1.0f, 0.6f, 0.32f, // Upper corner
		-0.5f,  0.5f, 0.0f,  0.9f, 0.45f, 0.17f // Inner left

	};


	GLuint indices[] = { // orders of indices

		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle

	};


	// initialize GLFW
	glfwInit();

	// what opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// <-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creat the window of size         |->        named
	GLFWwindow* window = glfwCreateWindow(1000, 800, "MakeShape", NULL, NULL);

	// cheack if window failed to be made
	if (window == NULL)
	{
		std::cout << "Failed to make GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// create shader object from using default.vert and defualt.frag
	Shader shaderProgram("Default.frag", "Default.vert");

	// generate vertex array and binds them
	VAO VAO1;
	VAO1.Bind();

	// makes the buffer objects and links it to the vertices/indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	// unbined them to provent unwanted changes
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		// take care of all events
	
		// change the colors
		glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.OnActivate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); 
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.OnDelete();

	//delete stuff before window close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}