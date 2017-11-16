#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// STB: Texture loader for several different types of image files
#include "stb_image.h"
// Shaders and camera class, based on Joey de Vries' camera and shader class from learnOpenGL.com.
#include "Camera.h"
#include "ObjectShader.h"
#include "LightShader.h"
#include "CubeMapShader.h"
// Dungeon class created by Thomas Angeland for creating random-generated dungeons in adjustable sizes.
#include "Dungeon.h"
// 3D Object classes
#include "CubeMap.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Diamond.h"
#include "Texture.h"
// 3D Light class
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
// General C++ (and C++11) libraries
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
// Text renderer by Vegard Strand
#include "Text.h"

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