#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// STB: Texture loader for several different types of image files
#include "stb_image.h"
// GLM: Matrix and vector math-library (temporary) 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// Shaders and camera class, based on Joey de Vries' camera and shader class from learnOpenGL.com.
#include "shader.h"
#include "camera.h"
// Dungeon class created by Thomas Angeland for creating random-generated dungeons in adjustable sizes.
#include "Dungeon.h"
// 3D Object classes
#include "Rectangle.h"
#include "Cube.h"
#include "Texture.h"
// General C++ (and C++11) libraries
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

class ThomasLevel
{
private: 
		GLFWwindow *window; 
		int WINDOW_WIDTH, WINDOW_HEIGHT;
		Dungeon dungeon;
public: 
	void init(GLFWwindow *window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	void loop();
};