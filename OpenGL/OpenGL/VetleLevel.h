#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

#include "CubeMap.h"
#include "Rectangle.h"
#include "Sphere.h"

#include "Texture.h"

namespace vetle {

	class VetleLevel
	{

	private:
		GLFWwindow *window;
		int WINDOW_WIDTH, WINDOW_HEIGHT;

	public:
		void init(GLFWwindow *window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
		void loop();


	};

};