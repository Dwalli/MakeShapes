#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include "texture.h"

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main()
{
	GLfloat vertices[] = { // vertices coordiants

		 0.5f,  0.5f, 0.0f,  0.8f, 0.3f,  0.02f,	0.0f, 0.0f, // Lower left corner
		 0.5f, -0.5f, 0.0f,  0.8f, 0.3f,  0.02f,	0.0f, 1.0f, // Lower right corner
		-0.5f, -0.5f, 0.0f,  1.0f, 0.6f,  0.32f,	1.0f, 1.0f, // Upper corner
		-0.5f,  0.5f, 0.0f,  0.9f, 0.45f, 0.17f,	1.0f, 0.0f // Inner left

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

	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	// unbined them to provent unwanted changes
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Adding texture

	int imageWidth, imageHight, noColorChanels;
	unsigned char* bytes = stbi_load("OIG.jpeg", &imageWidth, &imageHight, &noColorChanels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.OnActivate();
	glUniform1i(tex0Uni, 0);

	Texture Goblin("OIG_3.jpeg", GL_TEXTURE1, GL_TEXTURE_2D, GL_RGB);
	Goblin.LinkTexture("tex0", shaderProgram, 1);

	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		// take care of all events
	
		// change the colors
		glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.OnActivate();
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		Goblin.BindTexture();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); 
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	Goblin.OnDelete();
	shaderProgram.OnDelete();

	//delete stuff before window close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}