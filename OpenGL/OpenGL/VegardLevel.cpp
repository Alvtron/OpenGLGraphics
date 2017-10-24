#pragma once 
#include "VegardLevel.h"


void processInputVegard(GLFWwindow *window);

Text text;

void VegardLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
{
	this->window = window;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	this->WINDOW_WIDTH =  WINDOW_WIDTH;

	glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
	
	// Define the viewport dimensions
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


void VegardLevel::loop()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	processInputVegard(window);
	glfwSwapBuffers(window);
	glfwPollEvents();

}


void processInputVegard(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
