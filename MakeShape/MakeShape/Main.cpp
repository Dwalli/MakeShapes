#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// initialize GLFW
	glfwInit();

	// what opengl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// <-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creat the window of size         |->        named
	GLFWwindow* window = glfwCreateWindow(800, 800, "MakeShape", NULL, NULL);


	// cheack if window failed to be made
	if (window == NULL)
	{
		std::cout << "Faild to make GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// change the colors
	glClearColor(0.56f, 0.23f, 0.78f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	//main loop 
	while (!glfwWindowShouldClose(window))
	{
		// take care of all events
		glfwPollEvents();
	}

	//delete stuff before window close
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}