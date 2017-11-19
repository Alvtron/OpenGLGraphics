#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Text.h"



// Shaders and camera class, based on Joey de Vries' camera and shader class from learnOpenGL.com.
#include "ObjectShader.h"
#include "LightShader.h"
#include "CubeMapShader.h"

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

#include <string>
#include <vector>
#include <time.h>

//Test klasser
#include "Player.h"
#include "Entity.h"

namespace Vegard {

	class VegardLevel
	{

	private:
		GLFWwindow *window;
		GLuint WINDOW_WIDTH, WINDOW_HEIGHT;

	public:
		void init(GLFWwindow *window, int WINDOW_WIDTH, int WINDOW_HEIGHT);
		void loop();
		void update();
		void render();

	};
}