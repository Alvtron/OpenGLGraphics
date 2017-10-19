#pragma once
#include "ThomasLevel.h"

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Camera
Camera camera;
const glm::vec3 SPAWN_POSITION(0.0f, 2.0f, 2.0f);
double lastX;
double lastY;
bool firstMouse = true;

// Timing - time between current frame and last frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float rotation = 0.0f;

// Global positions
glm::vec3 lightPosition = glm::vec3(0.0f, 5.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 0.5f, 1.0f);

// 3D Objects
Cube cube = Cube();
Rect plane = Rect();

// Textures
Texture metal, tile;

// Shaders
Shader shader, lightShader;


void ThomasLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
{
	this->window = window;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	this->WINDOW_WIDTH = WINDOW_WIDTH;

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
	shader = Shader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
	lightShader = Shader("shaders/light_shader.vert", "shaders/light_shader.frag");

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================

	cube.storeOnGPU();
	plane.storeOnGPU();

	// ===========================================================================================
	// LOAD TEXTURES
	// ===========================================================================================
	metal = Texture();
	metal.addDiffuse("resources/textures/1857-diffuse.jpg");
	metal.addSpecular("resources/textures/1857-specexponent.jpg");
	metal.addNormal("resources/textures/1857-normal.jpg");

	tile = Texture();
	tile.addDiffuse("resources/textures/10744-diffuse.jpg");
	tile.addSpecular("resources/textures/10744-specstrength.jpg");
	tile.addNormal("resources/textures/10744-normal.jpg");
	tile.addAO("resources/textures/10744-ambientocclusion.jpg");

	Texture::SetShaderSampler(&shader);
	Texture::SetLightColor(&lightShader, lightColor);
}

void ThomasLevel::loop()
{
	// Per-frame time logic
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Process input (if any)
	processInput(window);

	// Background color (world color)
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Clear the depth buffer before each render iteration
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate shader when setting uniforms/drawing objects
	shader.use();
	shader.setVec3("light.position", lightPosition);
	shader.setVec3("viewPos", camera.Position);

	// light properties
	shader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f) + (lightColor * 0.1f));
	shader.setVec3("light.diffuse", lightColor * 0.5f);
	shader.setVec3("light.specular", lightColor);

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

	cube.drawObject(&shader, metal);
	cube.drawObject(&shader, glm::vec3(2.0f, 0.0f, 2.0f), tile);

	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);

	// Draw light object
	plane.drawObject(&lightShader, lightPosition, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f), metal);

	// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	glfwSwapBuffers(window);
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
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime, true);
		else
			camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime, true);
		else
			camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime, true);
		else
			camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime, true);
		else
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}
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