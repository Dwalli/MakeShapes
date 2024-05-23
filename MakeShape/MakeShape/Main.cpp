#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<stb/stb_image.h>
#include "texture.h"

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const unsigned int width = 1000;
const unsigned int hight = 800;



int main()
{
	GLfloat vertices[] = { // vertices coordiants

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f

	};


	GLuint indices[] = { // orders of indices

		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4

	};


	// initialize GLFW
	glfwInit();

	// what opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// <-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creat the window of size         |->        named
	GLFWwindow* window = glfwCreateWindow(width, hight, "MakeShape", NULL, NULL);

	// cheack if window failed to be made
	if (window == NULL)
	{
		std::cout << "Failed to make GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, hight);

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

	Texture Goblin("OIG.jpeg", GL_TEXTURE1, GL_TEXTURE_2D, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR);
	Goblin.LinkTexture("tex0", shaderProgram, 1);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		// take care of all events
	
		// change the colors
		glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.OnActivate();

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 240) {
			rotation += 0.5f;
			prevTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)(width / hight), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(model));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(model));


		glUniform1f(uniID, 0.5f);
		Goblin.BindTexture();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); 
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Goblin.OnDelete();
	shaderProgram.OnDelete();

	//delete stuff before window close
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}