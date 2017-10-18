#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class VegardLevel
{

private:
	GLFWwindow *window;
	int WINDOW_WIDTH, WINDOW_HEIGHT;

public:
	void init(GLFWwindow *window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	void loop();


};