#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>

class Level
{

private:

	GLFWwindow* window;
	int WINDOW_HEIGHT, WINDOW_WIDTH;
public:

	virtual void init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH) = 0;
	virtual void loop() = 0;

};