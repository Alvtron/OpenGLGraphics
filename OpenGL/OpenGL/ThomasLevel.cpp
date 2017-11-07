#pragma once
#include "ThomasLevel.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Camera
const vec3 SPAWN_POSITION(0.0f, 2.0f, 2.0f);
Camera camera(SPAWN_POSITION);
double lastX;
double lastY;
bool firstMouse = true;

// Timing - time between current frame and last frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float rotation = 0.0f;
float color_rotation_r = 0.0f;
float color_rotation_g = 0.0f;
float color_rotation_b = 0.0f;

// Light positions
vec3 sunPosition = vec3(-1.0, -1.0, 0.0f);
vec3 sunColor = vec3(1.0f, 1.0f, 0.0f);
std::vector<vec3> pointLightPositions = {
	vec3(0.7f,  2.0f,  2.0f),
	vec3(2.0f,  2.0f,  5.0f)
};
vec3 lightColor = vec3(1.0f, 0.5f, 1.0f);

// 3D Objects
CubeMap cubemap = CubeMap();
Cube cube = Cube(1.0f);
Diamond diamond = Diamond(1.0f);
Sphere light = Sphere(0.25f, 3);

// Textures
Texture metal, tile, mixedstone;

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
	//camera = Camera(SPAWN_POSITION);

	// ===========================================================================================
	// SHADER - Build and compile the shader program (with LearnOpenGL's provided shader class)
	// ===========================================================================================
	cubeMapShader = CubeMapShader("shaders/cubemap_vert.shader", "shaders/cubemap_frag.shader");
	shader = ObjectShader("shaders/object_vert.shader", "shaders/object_frag.shader");
	lightShader = LightShader("shaders/light_vert.shader", "shaders/light_frag.shader", lightColor);

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================
	cubemap.storeOnGPU();
	cube.storeOnGPU();
	diamond.storeOnGPU();
	light.storeOnGPU();

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
	metal.addDisplacement("resources/textures/1857-displacement.jpg");

	tile = Texture();
	tile.addDiffuse("resources/textures/10744-diffuse.jpg");
	tile.addSpecular("resources/textures/10744-specstrength.jpg");
	tile.addNormal("resources/textures/10744-normal.jpg");
	tile.addDisplacement("resources/textures/10744-displacement.jpg");

	mixedstone = Texture();
	mixedstone.addDiffuse("resources/textures/mixedstones-diffuse.jpg");
	mixedstone.addSpecular("resources/textures/mixedstones-specular.jpg");
	mixedstone.addNormal("resources/textures/mixedstones-normal.jpg");
	mixedstone.addDisplacement("resources/textures/mixedstones-displace.jpg");

	// ===========================================================================================
	// CREATE SHADOWS
	// ===========================================================================================

	/*const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
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
	shader.setInt("pointLightCount", pointLightPositions.size());
	shader.setInt("directionLightCount", pointLightPositions.size());
	shader.setFloat("material.shininess", 64.0f);
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("lightPos", pointLightPositions[0]);

	shader.setVec3("directionLight.direction", sunPosition);
	shader.setVec3("directionLight.ambient", vec3::scale(sunColor, 0.05f));
	shader.setVec3("directionLight.diffuse", vec3::scale(sunColor, 0.2f));
	shader.setVec3("directionLight.specular", vec3::scale(sunColor, 0.2f));

	// light properties
	for (int i = 0; i < pointLightPositions.size(); i++) {
		shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
		shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", vec3::scale(lightColor, 0.5f));
		shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", vec3::scale(lightColor, 0.5f));
		shader.setVec3("pointLights[" + std::to_string(i) + "].specular", vec3::scale(lightColor, 1.0f));
		shader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
		shader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
		shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
	}

	// Calculate View/Projection transformations
	mat4 projection = mat4::makePerspective(camera.Fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// -------------------------------------------------------------------------------------------
	// DRAW OBJECTS (see Rectangle/Cube class for draw functions)
	// -------------------------------------------------------------------------------------------
	
	for (int i = -10; i < 10; i++) {
		for (int j = -10; j < 10; j+=2) {
			cube.drawObject(&shader, vec3(i, 0.0f, j), tile);
			cube.drawObject(&shader, vec3(i, -0.25f, j + 1), metal);
		}
	}

	diamond.drawObject(&shader, vec3(0.0f, 3.0f, 0.0f), vec3(2.0f, 2.0f, 2.0f) , mixedstone);

	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);
	lightShader.SetLightColor(lightColor);

	// Draw light object
	for (int i = 0; i < pointLightPositions.size(); i++) {
		light.drawObject(&lightShader, pointLightPositions[i], 90.0f, vec3(1.0f, 0.0f, 0.0f), metal);
	}

	// Draw cubemap (this must AFTER all other objects last or it will decrease peformance)
	cubemap.drawCubemap(&cubeMapShader, &camera, view, projection);

	lightColor = vec3(abs(sin(color_rotation_r)), abs(sin(color_rotation_g)), abs(sin(color_rotation_b)));
	color_rotation_r += 0.05f * deltaTime;
	color_rotation_g += 0.15f * deltaTime;
	color_rotation_b += 0.30f * deltaTime;
	rotation = sin(color_rotation_r * M_PI);

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