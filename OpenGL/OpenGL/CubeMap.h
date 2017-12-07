#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <cmath>
#include "Shader.h"
#include "Camera.h"
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
	/* Default constructor */
	CubeMap();
	/* De-constructor */
	~CubeMap();
	/* Generate buffers and store vertex data on the GPU. Call drawCubemap(...) to draw it */
	void storeOnGPU();
	/* Load cubemap texture and attach it. You must provide a string-vector of 6 filepaths */
	void loadCubemapTexture(std::vector<std::string> faces);
	/* Load cubemap texture and attach it. You must provide 6 filepaths as Strings */
	void loadCubemapTexture(const std::string right, const std::string left, const std::string top, const std::string bottom, const std::string front, const std::string back);
	/* Draws the cubemap from vertex data stored on the GPU */
	void drawCubemap(Shader * shader, Camera * camera, mat4 projection);
};