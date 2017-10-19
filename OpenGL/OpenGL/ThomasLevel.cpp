#pragma once
#include "ThomasLevel.h"

// STB: Texture loader for several different types of image files
#include "..\OpenGL\src\stb_image.h"
// GLM: Matrix and vector math-library (temporary) 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// Shaders and camera class, based on Joey de Vries' camera and shader class from learnOpenGL.com.
#include "..\OpenGL\src\shader.h"
#include "..\OpenGL\src\camera.h"
// Dungeon class created by Thomas Angeland for creating random-generated dungeons in adjustable sizes.
#include "..\OpenGL\src\Dungeon.h"
// 3D Object classes
#include "..\OpenGL\src\Rectangle.h"
#include "..\OpenGL\src\Cube.h"


// General C++ (and C++11) libraries
#include <iostream>
#include <string>
#include <vector>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// Camera
Camera camera;
const glm::vec3 SPAWN_POSITION = glm::vec3(0.0f, 2.0f, 3.0f);
double lastX;
double lastY;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// Global positions
glm::vec3 lightPosition = glm::vec3(0.0f, 5.0f, 0.0f);



//---------------------------------->VEGARD
Cube cube = Cube();
Rect plane = Rect(4.0f, 4.0f);

//------------------------------->VEGARD 
Shader shader;
Shader lightShader;

unsigned int tx_diff;
unsigned int tx_spec;


void ThomasLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
{

	this->window = window;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	this->WINDOW_WIDTH = WINDOW_WIDTH;

	//-------------------------------->VEGARD HER måtte jeg gjøre noe forandringer på dine globale variabler

	lastX = WINDOW_WIDTH / 2.0f;
	lastY = WINDOW_HEIGHT / 2.0f;

	// Set actionlisteners for window resize, mouse and scrolling
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Tell GLFW to capture the players mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// ===========================================================================================
	// CAMERA - for player movement, sets spawn position
	// ===========================================================================================
	camera = Camera(SPAWN_POSITION);



	// ===========================================================================================
	// SHADER - Build and compile the shader program (with LearnOpenGL's provided shader class)
	// ===========================================================================================
	shader = Shader("src/shaders/vertex_shader.vert", "src/shaders/fragment_shader.frag");
	lightShader = Shader("src/shaders/light_shader.vert", "src/shaders/light_shader.frag");

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================


	cube.storeOnGPU();

	plane.storeOnGPU();

	// ===========================================================================================
	// LOAD TEXTURES
	// ===========================================================================================
	tx_diff = loadTexture(std::string("src/resources/textures/1857-diffuse.jpg").c_str());
	tx_spec = loadTexture(std::string("src/resources/textures/1857-specexponent.jpg").c_str());

	// Texture shading configuration
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

}

void ThomasLevel::loop()
{
	// ===========================================================================================
	// RENDER LOOP
	// ===========================================================================================

	// Per-frame time logic
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Process input (if any)
	processInput(this->window);

	// Background color (world color)
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Clear the depth buffer before each render iteration
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate shader when setting uniforms/drawing objects


	shader.use();
	shader.setVec3("light.position", lightPosition);
	shader.setVec3("viewPos", camera.Position);

	// light properties
	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	shader.setFloat("material.shininess", 64.0f);

	// Calculate View/Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// -------------------------------------------------------------------------------------------
	// DRAW OBJECTS (see Rectangle/Cube class for draw functions)
	// -------------------------------------------------------------------------------------------

	cube.drawObject(
		&shader,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		tx_diff, tx_spec
	);

	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);

	// Draw light object
	plane.drawObject(
		&lightShader,
		lightPosition,
		glm::vec3(1.0f, 1.0f, 1.0f),
		90.0f,
		glm::vec3(1.0f, 0.0f, 0.0f),
		tx_diff, tx_spec
	);
	// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	glfwSwapBuffers(this->window);
	glfwPollEvents();


}


// ===========================================================================================
// PLAYER INPUTS
// ===========================================================================================
// Process all input: Query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// GLFW: whenever the window size changes, this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// GLFW: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.setFOV((float)yoffset);
}

// Utillity function for loading a 2D texture from file (Created by Joey de Vries, copied the 27.09.2017 from https://learnopengl.com/) 
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}