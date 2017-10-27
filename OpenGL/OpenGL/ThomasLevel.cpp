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
float color_rotation_r = 0.0f;
float color_rotation_g = 0.0f;
float color_rotation_b = 0.0f;

// Global positions
std::vector<glm::vec3> pointLightPositions = {
        glm::vec3( 0.7f,  2.0f,  2.0f),
        glm::vec3( 2.3f,  4.0f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  1.0f, -3.0f)
    };
glm::vec3 lightColor = glm::vec3(1.0f, 0.5f, 1.0f);

// 3D Objects
CubeMap cubemap = CubeMap();
Cube cube = Cube();
Rect plane = Rect();

// Textures
Texture metal, tile;

// Shaders
CubeMapShader cubeMapShader;
ObjectShader shader;
LightShader lightShader;

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
	cubeMapShader = CubeMapShader("shaders/cubemap.vert", "shaders/cubemap.frag");
	shader = ObjectShader("shaders/object.vert", "shaders/object.frag");
	lightShader = LightShader("shaders/light.vert", "shaders/light.frag", lightColor);

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================
	cubemap.storeOnGPU();
	cube.storeOnGPU();
	plane.storeOnGPU();

	// ===========================================================================================
	// LOAD TEXTURES
	// ===========================================================================================
	cubemap.loadCubemapTexture(
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/back.jpg",
		"resources/skybox/front.jpg"
	);

	metal = Texture();
	metal.addDiffuse("resources/textures/1857-diffuse.jpg");
	metal.addSpecular("resources/textures/1857-specexponent.jpg");
	metal.addNormal("resources/textures/1857-normal.jpg");

	tile = Texture();
	tile.addDiffuse("resources/textures/10744-diffuse.jpg");
	tile.addSpecular("resources/textures/10744-specstrength.jpg");
	tile.addNormal("resources/textures/10744-normal.jpg");
	tile.addAO("resources/textures/10744-ambientocclusion.jpg");

	// ===========================================================================================
	// CREATE SHADOWS
	// ===========================================================================================

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	shader.setFloat("material.shininess", 64.0f);
	shader.setVec3("viewPos", camera.Position);

	// light properties
	for (int i = 0; i < pointLightPositions.size(); i++) {
		shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
		shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", glm::vec3(0.2f, 0.2f, 0.2f) + (lightColor * 0.1f));
		shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", lightColor * 0.5f);
		shader.setVec3("pointLights[" + std::to_string(i) + "].specular", lightColor);
		shader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
		shader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
		shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032);
	}

	// Calculate View/Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// -------------------------------------------------------------------------------------------
	// DRAW OBJECTS (see Rectangle/Cube class for draw functions)
	// -------------------------------------------------------------------------------------------
	
	for (int i = -10; i < 10; i++) {
		for (int j = -10; j < 10; j+=2) {
			cube.drawObject(&shader, glm::vec3(i, 0.0f, j), tile);
			cube.drawObject(&shader, glm::vec3(i, 0.0f, j + 1), metal);
		}
	}

	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);
	lightShader.SetLightColor(lightColor);

	// Draw light object
	for (int i = 0; i < pointLightPositions.size(); i++) {
		plane.drawObject(&lightShader, pointLightPositions[i], 90.0f, glm::vec3(1.0f, 0.0f, 0.0f), metal);
	}

	// Draw cubemap (this must AFTER all other objects last or it will decrease peformance)
	cubemap.drawCubemap(&cubeMapShader, &camera, view, projection);

	lightColor = glm::vec3(abs(sin(color_rotation_r)), abs(sin(color_rotation_g)), abs(sin(color_rotation_b)));
	color_rotation_r += 0.10f * deltaTime;
	color_rotation_g += 0.20f * deltaTime;
	color_rotation_b += 0.30f * deltaTime;

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