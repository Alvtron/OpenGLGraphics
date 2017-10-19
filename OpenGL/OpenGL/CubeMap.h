#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"
#include <cmath>
#include "Shader.h"
#include "camera.h"
#include <iostream>
#include <iomanip>
#include <vector>

class CubeMap
{
private:
	unsigned int texture_id, VAO, VBO;
	const float VERTICES[108] = {
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,

		-1.0f,	-1.0f,	+1.0f,
		-1.0f,	-1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	-1.0f,
		-1.0f,	+1.0f,	+1.0f,
		-1.0f,	-1.0f,	+1.0f,

		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,

		-1.0f,	-1.0f,	+1.0f,
		-1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	-1.0f,	+1.0f,
		-1.0f,	-1.0f,	+1.0f,

		-1.0f,	+1.0f,	-1.0f,
		+1.0f,	+1.0f,	-1.0f,
		+1.0f,	+1.0f,	+1.0f,
		+1.0f,	+1.0f,	+1.0f,
		-1.0f,	+1.0f,	+1.0f,
		-1.0f,	+1.0f,	-1.0f,

		-1.0f,	-1.0f,	-1.0f,
		-1.0f,	-1.0f,	+1.0f,
		+1.0f,	-1.0f,	-1.0f,
		+1.0f,	-1.0f,	-1.0f,
		-1.0f,	-1.0f,	+1.0f,
		+1.0f,	-1.0f,	+1.0f
	};
public:
	CubeMap();
	~CubeMap();
	void storeOnGPU();
	void loadCubemapTexture(std::vector<std::string> faces);
	void loadCubemapTexture(const std::string right, const std::string left, const std::string top, const std::string bottom, const std::string front, const std::string back);
	void drawCubemap(Shader * shader, Camera * camera, glm::mat4 view, glm::mat4 projection);
};