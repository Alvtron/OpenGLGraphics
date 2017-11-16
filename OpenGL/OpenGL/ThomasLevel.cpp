#pragma once
#include "ThomasLevel.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void renderObjects(mat4 projection, mat4 view);
void renderLights(mat4 projection, mat4 view);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Camera
const vec3 SPAWN_POSITION(0.0f, 2.0f, 0.0f);
Camera camera(SPAWN_POSITION);
double lastX;
double lastY;
bool firstMouse = true, wireframe_mode = false;

// Timing - time between current frame and last frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float rotation = 0.0f;
float color_rotation_r = 0.0f;
float color_rotation_g = 0.0f;
float color_rotation_b = 0.0f;

// Lights
std::vector<Light> lights;
vec3 sunPosition = vec3(-1.0, -1.0, 0.0f);
vec3 sunColor = vec3(1.0f, 1.0f, 0.0f);
vec3 lightColor = vec3(1.0f, 0.5f, 1.0f);
SpotLight flashlight = SpotLight(&camera, vec3(1.0f));

// 3D Objects
CubeMap cubemap = CubeMap();
Cube cube = Cube(1.0f);
Diamond diamond = Diamond(1.0f);
Sphere light = Sphere(0.25f, 3);
Rect rect = Rect();

// Textures
Texture metal, tile, mixedstone;

// Shaders
Shader waterShader;
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
	glfwSetKeyCallback(window, key_callback);

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
	waterShader = Shader("shaders/water_vert.shader", "shaders/water_frag.shader");

	// ===========================================================================================
	// 3D LIGHTS - Set up lights
	// ===========================================================================================
	flashlight.disable();

	lights.push_back(DirectionalLight(sunColor, sunPosition));
	lights.push_back(PointLight(vec3(0.0f), vec3(0.7f, 2.0f, 2.0f)));
	lights.push_back(PointLight(vec3(0.0f), vec3(2.0f, 2.0f, 5.0f)));

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================
	cubemap.storeOnGPU();
	cube.storeOnGPU();
	diamond.storeOnGPU();
	light.storeOnGPU();
	rect.storeOnGPU();
	rect.setScale(vec3(10.0f, 10.0f, 0.0f));
	rect.setRotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

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

	color_rotation_r += 0.05f * deltaTime;
	color_rotation_g += 0.15f * deltaTime;
	color_rotation_b += 0.30f * deltaTime;
	lightColor = vec3(abs(sin(color_rotation_r)), abs(sin(color_rotation_g)), abs(sin(color_rotation_b)));
	rotation = (float)sin(color_rotation_r * M_PI);

	// Background color (world color)
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Clear the depth buffer before each render iteration
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate View/Projection transformations
	mat4 projection = mat4::makePerspective(camera.Fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	mat4 view = camera.GetViewMatrix();

	renderObjects(projection, view);
	renderLights(projection, view);
	
	// Draw cubemap (this must happen last or it will decrease peformance)
	cubemap.drawCubemap(&cubeMapShader, &camera, view, projection);

	// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	glfwSwapBuffers(window);
	glfwPollEvents();
}

/* DRAW OBJECTS - set up shaders and call mesh draw functions */
void renderObjects(mat4 projection, mat4 view) {
	// Activate shader when setting uniforms/drawing objects
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setFloat("material.shininess", 64.0f);
	shader.setVec3("viewPos", camera.Position);

	// lights
	shader.setInt("directionLightCount", Light::numDirectionalLights());
	shader.setInt("pointLightCount", Light::numPointLights());
	shader.setInt("spotLightCount", Light::numSpotLights());
	shader.setInt("lightCount", lights.size());

	for (int i = 0; i < lights.size(); i++) {
		shader.setVec3("lightPositions[" + std::to_string(i) + "]", lights.at(i).position);
		lights.at(i).drawLight(&shader);
	}

	flashlight.drawLight(&shader);
	
	for (int i = -10; i < 10; i++)
	for (int j = -10; j < 10; j+=2) {
	cube.drawObject(&shader, vec3((float)i, 0.0f, (float)j), tile);
	cube.drawObject(&shader, vec3((float)i, -0.25f, (float)j + 1.0f), metal);
	}

	diamond.drawObject(&shader, vec3(0.0f, 3.0f, 0.0f), vec3(2.0f, 2.0f, 2.0f), mixedstone);

	// DRAW WATER - set up water shader and call mesh draw functions
	waterShader.use();
	waterShader.setMat4("projection", projection);
	waterShader.setMat4("view", view);
	rect.setScale(vec3(50.0f, 0.f, 50.0f));
	rect.drawObject(&waterShader, mixedstone);
}

/* DRAW LIGHTS - set up light shader and call mesh draw functions */
void renderLights(mat4 projection, mat4 view) {
	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);
	lightShader.SetLightColor(lightColor);

	// Draw light object
	for (int i = 0; i < lights.size(); i++) {
		if (lights.at(i).is(Light::POINT)) {
			light.drawObject(&lightShader, lights.at(i).position, 90.0f, vec3(1.0f, 0.0f, 0.0f), metal);
			lights.at(i).color = lightColor;
		}
	}
}

// ===========================================================================================
// PLAYER INPUTS
// ===========================================================================================
/* Process all input: Query GLFW whether relevant keys are pressed/released this frame and react accordingly */
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
}

/* Process all input: Query GLFW whether relevant keys are pressed. Registers one press. */
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (flashlight.isEnabled())
			flashlight.disable();
		else
			flashlight.enable();
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		if (wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		wireframe_mode = !wireframe_mode;
	}
}

/* GLFW: whenever the window size changes, this callback function executes */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/* GLFW: whenever the mouse moves, this callback is called */
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

/* GLFW: whenever the mouse scroll wheel scrolls, this callback is called */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.setFOV((float)yoffset);
}