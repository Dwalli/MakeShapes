#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main()
{
	// initialize GLFW
	glfwInit();

	// what opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// <-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = { // vertices coordiants

		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	GLuint indices[] = { // orders of indices

		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle

	};

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
	Shader shaderProgram("Default.vert", "Default.frag");

	// generate vertex array and binds them
	VAO VAO1;
	VAO1.Bind();

	// makes the buffer objects and links it to the vertices/indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);

	// unbined them to provent unwanted changes
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		// take care of all events
	
		// change the colors
		glClearColor(0.56f, 0.23f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.OnActivate();
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