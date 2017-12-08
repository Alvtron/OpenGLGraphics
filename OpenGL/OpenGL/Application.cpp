#pragma once
// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Math
#include "MathDefinitions.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// STB: Texture loader for several different types of image files
#include "stb_image.h"
// Shader Classes
#include "Shader.h"
#include "Framebuffer.h"


// 3D Object classes
#include "CubeMap.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Diamond.h"
// Texture Classes
#include "Texture.h"
#include "Material.h"
#include "CloudTexture.h"
// 3D Light class
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

// Entities
#include "Player.h"
#include "Entity.h"


// Text renderer by Vegard Strand
#include "Text.h"
// General C++ (and C++11) libraries
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Presets
#define DEBUG true
#define FULLSCREEN false
#define MSAA_SAMPLES 4
#define DRAW_WIREFRAME false
double getTimeSeconds(clock_t time_begin, clock_t time_end);
clock_t start_time_init;

//Enables Vsync
bool vsync = true;

// Window
const char window_title[] = "ITF21215 OpenGL group project";
const int openGL_min = 4, openGL_max = 4;
GLFWwindow* window;
unsigned int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 700;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void renderObjects(mat4 projection, mat4 view);
void renderLights(mat4 projection, mat4 view);
void processInput(GLFWwindow *window,float deltaTime);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void renderQuad();

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float increment_0 = 0.0f, increment_1 = 0.0f, increment_2 = 0.0f, increment_3 = 0.0f;

// Render quad VAO and VBO
static unsigned int quad_vao = 0;
static unsigned int quad_vbo = 0;

// Other global variables
bool bloom = false, render_clouds = false;
float exposure = 1.0f;
float cloud_render_distance = 1000.0f;
float cloud_coverage = 0.4;

//Entities for collision and camera
const vec3 SPAWN_POSITION(0.0f, 10.0f, 0.0f);
Player player;
Entity gorundEntity(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0001f, 1.0f), vec3(100.0f, 100.0f, 100.0f), true);
Entity boxEnt(vec3(0.0f, 1.5f, -20.0f), vec3(1.0f, 1.0f, 1.0f), vec3(3.0f, 3.0f, 3.0f), true);
Entity dimodEnt(vec3(5.0f, 0.5f, -10.0f), vec3(1.0f, 1.0f, 1.0f), vec3(2.5f, 2.5f, 2.5f), false, true);
//Rotating dimand degrees
float rotatingDimond = 0.0f;

double lastX;
double lastY;
bool firstMouse = true;
bool flyingMode = false;
bool invertedMouse = false;

//Text
Text text;
bool playerConsole = true;
bool holdTab = false;
std::string keyInputMenu = "WASD = movement | SPACE = Jump | I = inverted mouse controls | F1 = on/off clouds | 1/2 = clouds render distance"; //<-- Legg til her
std::string keyInputMenu2 = "B = on/off Bloom | Q/E = increasing/decreasing bloom | G = on/off collision and gravity ";

// Lights
std::vector<Light> lights;
vec3 sunDirection = vec3(-1.0, -1.0, 0.0f);
vec3 sunPosition = vec3(1000.0f, 1000.0f, 0.0f);
vec3 sunColor = vec3(1.0f, 1.0f, 0.5f);
vec3 lightColor = vec3(1.0f, 0.5f, 1.0f);
SpotLight flashlight = SpotLight(&player.camera, vec3(1.0f));

// Framebuffers
Framebuffer cloudFBO;
Framebuffer sceneFBO;
Framebuffer pingpongFBO[2];

// Shaders
Shader objectShader, lightShader, blurShader, bloomShader, cloudShader, cubeMapShader;

// Cubemap
CubeMap cubemap = CubeMap();

// Objects
Cube cube = Cube(1.0f);
Cube cubehit = Cube(boxEnt.scale.x);
Diamond diamond = Diamond(1.0f);
Diamond diamondPickUp = Diamond(1.0f);
Sphere light = Sphere(0.25f, 3);
Sphere sphere_low = Sphere(1.0f, 1);
Sphere sphere_medium = Sphere(1.0f, 2);
Sphere sphere_high = Sphere(1.0f, 4);
Rect rect = Rect(1.0f, 1.0f);

// Textures & Materials
Material metal, tile, mixedstone;
Texture cloud_texture, cloud_structure_texture;

void initGLFWindow()
{
	if (DEBUG) {
		printf("% DEBUG MODUS %\n\n");
		start_time_init = clock();
	}

	// Initialize GLFW
	int glfw = glfwInit();

	if (glfw == GLFW_FALSE)
	{
		printf("Error: Failed to initialize GLFW\n");
		return;
	}
	// Set GLFW to use OpenGL version 4.5, both minor and major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_max);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_min);
	// Get access to a smaller subset of OpenGL features (no backwards-compatibility)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Use multisample buffer with 4 samples (MSAA)
	glfwWindowHint(GLFW_SAMPLES, MSAA_SAMPLES);

	// Create a window and it's OpenGL context

	if (FULLSCREEN) window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title, glfwGetPrimaryMonitor(), NULL);
	else window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title, NULL, NULL);
	if (!window)
	{
		printf("Error: Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	//Enable vsync
	glfwSwapInterval(vsync);

	// Configure global OpenGL state
	glEnable(GL_DEPTH_TEST);
	// Enable MSAA Anti-Aliasing
	glEnable(GL_MULTISAMPLE);
	// Enable gamma correction with OpenGL built in sRGB buffer
	glEnable(GL_FRAMEBUFFER_SRGB);

	glewExperimental = GL_TRUE;

	// Initialize GLEW and check if it's OK
	GLenum glew = glewInit();
	if (GLEW_OK != glew)
	{
		printf("Error: %s\n", glewGetErrorString(glew));
		return;
	}
	if (DEBUG) {
		printf("OpenGL version %s\n", glGetString(GL_VERSION));
		printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}
}


void main()
{
	//init GLFW window
	initGLFWindow();

	// Draw wireframe
	if (DRAW_WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	printf("\nSetting up GLFW...\n");

	lastX = WINDOW_WIDTH / 2.0f;
	lastY = WINDOW_HEIGHT / 2.0f;

	// Set actionlisteners for window resize, mouse and scrolling
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//Blending proporties
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Init fonts and gets native fonts from windows
	text.initFonts("C:/Windows/Fonts/Arial.ttf", WINDOW_HEIGHT, WINDOW_WIDTH);

	// Tell GLFW to capture the players mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ===========================================================================================
	// SHADER - Build and compile shader programs
	// ===========================================================================================
	printf("\nSetting up shaders...\n");

	printf("Loading object shader...\n");
	if (objectShader.init("shaders/object_vert.shader", "shaders/object_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	printf("Loading light shader...\n");
	if (lightShader.init("shaders/light_vert.shader", "shaders/light_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	printf("Loading cubemap shader...\n");
	if (cubeMapShader.init("shaders/cubemap_vert.shader", "shaders/cubemap_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	printf("Loading cloud shader...\n");
	if (cloudShader.init("shaders/cloud_vert.shader", "shaders/cloud_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	printf("Loading blur shader...\n");
	if (blurShader.init("shaders/blur_vert.shader", "shaders/blur_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	printf("Loading bloom shader...\n");
	if (bloomShader.init("shaders/bloom_vert.shader", "shaders/bloom_frag.shader") != 0) {
		printf("Error: Failed to initialize shader in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	objectShader.use();
	objectShader.setInt("material.diffuse", 0);
	objectShader.setInt("material.specular", 1);
	objectShader.setInt("material.normal", 2);
	objectShader.setInt("material.displacement", 3);
	objectShader.setInt("material.ao", 4);

	cubeMapShader.use();
	cubeMapShader.setInt("skybox", 0);

	cloudShader.use();
	cloudShader.setInt("diffuse_buffer", 10);
	cloudShader.setInt("depth_buffer", 11);

	blurShader.use();
	blurShader.setInt("image", 0);
	bloomShader.use();
	bloomShader.setInt("HDR_buffer", 0);
	bloomShader.setInt("bloom_blur", 5);

	// ===========================================================================================
	// FRAMEBUFFERS
	// ===========================================================================================
	printf("\nSetting up framebuffers...\n");

	// Scenery framebuffer
	sceneFBO.createSceneFramebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Clouds framebuffer
	cloudFBO.createCloudFramebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// ping-pong framebuffer for blurring
	Framebuffer::createPingPongFramebuffer(pingpongFBO, WINDOW_WIDTH, WINDOW_HEIGHT);

	// ===========================================================================================
	// LIGHTS - Set up lights
	// ===========================================================================================
	printf("\nSetting up lights...\n");

	flashlight.disable();

	lights.push_back(DirectionalLight(sunColor, sunDirection));
	lights.push_back(PointLight(vec3(1.0f), vec3(0.0f)));
	lights.push_back(PointLight(vec3(1.0f), vec3(0.0f)));

	// ===========================================================================================
	// OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================
	printf("\nSetting up objects...\n");

	cubemap.storeOnGPU();
	cube.storeOnGPU();
	cubehit.storeOnGPU();
	diamond.storeOnGPU();
	diamondPickUp.storeOnGPU();
	light.storeOnGPU();

	sphere_low.storeOnGPU();
	sphere_medium.storeOnGPU();
	sphere_high.storeOnGPU();

	rect.storeOnGPU();

	// ===========================================================================================
	// LOAD TEXTURES
	// ===========================================================================================
	printf("\nSetting up textures...\n");

	cubemap.loadCubemapTexture(
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/back.jpg",
		"resources/skybox/front.jpg"
	);

	metal.addDiffuse(Texture("resources/textures/1857-diffuse.jpg"));
	metal.addSpecular(Texture("resources/textures/1857-specexponent.jpg"));
	metal.addNormal(Texture("resources/textures/1857-normal.jpg"));
	metal.addDisplacement(Texture("resources/textures/1857-displacement.jpg"));

	tile.addDiffuse(Texture("resources/textures/10744-diffuse.jpg"));
	tile.addSpecular(Texture("resources/textures/10744-specstrength.jpg"));
	tile.addNormal(Texture("resources/textures/10744-normal.jpg"));
	tile.addDisplacement(Texture("resources/textures/10744-displacement.jpg"));

	mixedstone.addDiffuse(Texture("resources/textures/mixedstones-diffuse.jpg"));
	mixedstone.addSpecular(Texture("resources/textures/mixedstones-specular.jpg"));
	mixedstone.addNormal(Texture("resources/textures/mixedstones-normal.jpg"));
	mixedstone.addDisplacement(Texture("resources/textures/mixedstones-displace.jpg"));

	printf("\nLoading 3D cloud texture...\n");
	if (createTexture3DFromEX5(&cloud_texture, "resources/textures/noise5.ex5") == false) {
		printf("ERROR :: Failed to load texture in %s at line %d.\n\n", __FILE__, __LINE__);
	}

	// Preprocess the structure of the noise based clouds
	printf("Preprocessing cloud structure...");
	CloudTexture::process(&cloud_structure_texture, cloud_texture);

	// Send textures to shaders
	cloudShader.setTexture3D(cloud_texture, "cloud_texture");
	cloudShader.setTexture3D(cloud_structure_texture, "cloud_structure");

	// ===========================================================================================
	// ENTITIES / PLAYER
	// ===========================================================================================
	player.position = SPAWN_POSITION;
	player.hitbox = vec3(0.5f, 1.0f, 0.5f);
	player.camera.SetCameraPosition(player.position);
	player.addCollidableEntity(gorundEntity);
	player.addCollidableEntity(boxEnt);
	player.addCollidableEntity(dimodEnt);

	if (DEBUG) {
		printf("\n\nInitialization time: %f seconds", getTimeSeconds(start_time_init, clock()));
	}
	// ===========================================================================================
	// GAME LOOP / RENDER LOOP
	// ===========================================================================================
	printf("\n\nStarting game loop...\n");
	while (!glfwWindowShouldClose(window)) {

		// Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input (if any)
		processInput(window, deltaTime);

		increment_0 += 0.05f * deltaTime;
		increment_1 += 0.15f * deltaTime;
		increment_2 += 0.30f * deltaTime;
		increment_3 += 1.0f * deltaTime;
		lightColor = vec3(abs(sin(increment_0)), abs(sin(increment_1)), abs(sin(increment_2)));

		// Background color (world color)
		sunPosition = player.camera.Position + vec3(1337, 1337, 1337);

		/* Calculate view and projection matrices and send them to shaders */

		mat4 view = player.camera.GetViewMatrix();
		mat4 projection = mat4::makePerspective(player.camera.Fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

		cloudShader.setMat4("view", view);
		cloudShader.setMat4("proj", projection);
		cloudShader.setMat4("inv_view", mat4::inverse(view));
		cloudShader.setMat4("inv_proj", mat4::inverse(projection));
		cloudShader.setVec2("window_size", vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
		cloudShader.setVec3("camera_position", vec3(0.0f, 0.0f, increment_2 * 10));
		cloudShader.setVec3("sun_position", sunPosition);
		cloudShader.setFloat("end", cloud_render_distance);
		cloudShader.setFloat("coverage", cloud_coverage);

		/*** OpenGL rendering ***/

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// -----------------------------------------------
		// 1. render terrain and sky
		// -----------------------------------------------

		sceneFBO.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render objects & light
		renderLights(projection, view);
		renderObjects(projection, view);

		// Draw cubemap
		cubemap.drawCubemap(&cubeMapShader, &player.camera, projection);


		// -----------------------------------------------
		// 2. render clouds
		// -----------------------------------------------
		
		if (render_clouds) {
			// Render clouds with resolve shader
			cloudFBO.bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cloudShader.use();

			glActiveTexture(GL_TEXTURE10);
			glBindTexture(GL_TEXTURE_2D, sceneFBO.colorBuffer[0]);

			renderQuad();
		}
		
		// -----------------------------------------------
		// 3. render text
		// -----------------------------------------------
		if (playerConsole) {
			text.RenderText(player.consolePlayerPosition(), 20.0f, 20.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(player.consolePlayerCollision(), 20.0f, 60.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(player.consoleOtherTings(), 20.0f, 100.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
		}

		if (player.interactWithEntity)
		{
			text.RenderText("Press E", WINDOW_WIDTH / 2 - 20.0f, WINDOW_HEIGHT / 2, 0.7f, vec3(1.0f, 0.0f, 0.0f));
		}
		if(!holdTab)
			text.RenderText("Hold TAB for key-menu", 20.0f, WINDOW_HEIGHT - 40.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));	
		else {
			text.RenderText(keyInputMenu, 20.0f, WINDOW_HEIGHT - 40.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(keyInputMenu2, 20.0f, WINDOW_HEIGHT - 80.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));

		}

		// -----------------------------------------------
		// 4. blur scene
		// -----------------------------------------------

		// This code executes the Gaussian blur. Here we blur the image 30 times, the more we iterate the blurring process, the more blur will be on
		// the image. Each iteration, the boolean horizontal will change, so it blurs horizontally first, then vertically, into alternating framebuffers.
		//
		bool horizontal = true, first_iteration = true;
		unsigned int amount = 30;
		blurShader.use();
		for (unsigned int i = 0; i < amount; i++)
		{
			pingpongFBO[horizontal].bind();
			blurShader.setInt("horizontal", horizontal);
			glActiveTexture(GL_TEXTURE0);
			// bind texture of other framebuffer (or scene if first iteration)
			glBindTexture(GL_TEXTURE_2D, first_iteration ? sceneFBO.colorBuffer[1] : pingpongFBO[!horizontal].colorBuffer[0]);
			renderQuad();
			horizontal = !horizontal;
			if (first_iteration)
				first_iteration = false;
		}


		// -----------------------------------------------
		// 5. render fbo color buffers
		// -----------------------------------------------

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		bloomShader.use();

		if (render_clouds) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cloudFBO.colorBuffer[0]);
		} else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sceneFBO.colorBuffer[0]);
		}

		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, pingpongFBO[!horizontal].colorBuffer[0]);

		bloomShader.setInt("bloom", bloom);
		bloomShader.setFloat("exposure", exposure);

		renderQuad();

		// -----------------------------------------------
		// Swap buffers
		// -----------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

// Calculate time passed between two timestamps and return it in seconds
double getTimeSeconds(clock_t time_begin, clock_t time_end) {
	return double(time_end - time_begin) / CLOCKS_PER_SEC;
}

/* DRAW OBJECTS - set up shaders and call vertex draw functions */
void renderObjects(mat4 projection, mat4 view) {
	// Activate shader when setting uniforms/drawing objects
	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", view); 
	objectShader.setFloat("material.shininess", 64.0f);
	objectShader.setVec3("viewPos", player.camera.Position);

	// lights
	objectShader.setInt("directionLightCount", Light::numDirectionalLights());
	objectShader.setInt("pointLightCount", Light::numPointLights());
	objectShader.setInt("spotLightCount", Light::numSpotLights());
	objectShader.setInt("lightCount", lights.size());

	for (int i = 0; i < lights.size(); i++) {
		objectShader.setVec3("lightPositions[" + std::to_string(i) + "]", lights.at(i).position);
		lights.at(i).drawLight(&objectShader);
	}

	flashlight.drawLight(&objectShader);

	cube.drawObject(&objectShader, vec3(0.0f, 5.0f, 0.0f), &metal);
	cubehit.drawObject(&objectShader, boxEnt.position, &metal);
	//rect.setScale(gorundEntity.scale);
	rect.drawObject(&objectShader, gorundEntity.position, gorundEntity.scale, &tile);

	diamond.drawObject(&objectShader, vec3(0.0f, 3.0f, -3.0f), vec3(2.0f, 2.0f, 2.0f), &mixedstone);

	//PickUpItems
	if (player.entities[2].exist) {
		diamondPickUp.drawObject(&objectShader, dimodEnt.position, vec3(0.5f, 0.5f, 0.5f), rotatingDimond, vec3(0.0f, 1.0f, 0.0f), &metal);
		rotatingDimond += 0.8;
	}

	sphere_low.drawObject(&objectShader, vec3(20.0f, 2.0f, 0.0f), &tile);
	sphere_medium.drawObject(&objectShader, vec3(20.0f, 2.0f, 2.0f), &tile);
	sphere_high.drawObject(&objectShader, vec3(20.0f, 2.0f, 4.0f), &tile);

}

/* DRAW LIGHTS - set up light shader and call vertex draw functions */
void renderLights(mat4 projection, mat4 view) {
	// Activate light shader and configure it
	lightShader.use();
	lightShader.setMat4("projection", projection);
	lightShader.setMat4("view", view);
	lightShader.setBool("hasLightColor", true);

	// Draw light object
	for (int i = 0; i < lights.size(); i++) {
		lightShader.setVec3("lightColor", lightColor);
		if (lights.at(i).is(Light::POINT)) {
			lights.at(i).position = vec3(sin(increment_3) * 10 + i, 2.0f, cos(increment_3) * 10 + i), 90.0f, vec3(1.0f, 0.0f, 0.0f);
			light.drawObject(&lightShader, lights.at(i).position, nullptr);
			lights.at(i).color = lightColor;
		}
	}

}

// ===========================================================================================
// PLAYER INPUTS
// ===========================================================================================
/* Process all input: Query GLFW whether relevant keys are pressed/released this frame and react accordingly */
void processInput(GLFWwindow *window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	player.processInput(window, deltaTime, true);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (exposure > 0.0f)
			exposure -= 0.01f;
		else
			exposure = 0.0f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		exposure += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		if (cloud_render_distance > 0.0f)
			cloud_render_distance -= 1.0f;
		else
			cloud_render_distance = 0.0f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		if (cloud_render_distance < 10000.0f)
			cloud_render_distance += 1.0f;
		else
			cloud_render_distance = 10000.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		if (cloud_coverage < 1.0f)
			cloud_coverage += 0.001f;
		else
			cloud_coverage = 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		if (cloud_coverage > 0.35f)
			cloud_coverage -= 0.001f;
		else
			cloud_coverage = 0.35f;
	}


	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		holdTab = true;
	else
		holdTab = false;

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
		render_clouds = !render_clouds;
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		flyingMode = !flyingMode;
		player.isFlying = flyingMode;
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS)
		invertedMouse = !invertedMouse;

	if (key == GLFW_KEY_B && action == GLFW_PRESS)
		bloom = !bloom;

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
	double yoffset;

	if(invertedMouse)
		yoffset = ypos - lastY; // Inverted mouse controls
	else
		yoffset = lastY - ypos; // Not inverted mouse controls

	lastX = (float)xpos;
	lastY = (float)ypos;

	player.camera.ProcessMouseMovement(xoffset, yoffset);
}

/* GLFW: whenever the mouse scroll wheel scrolls, this callback is called */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	player.camera.setFOV((float)yoffset);
}

void renderQuad()
{
	if (quad_vao == 0) {
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		glGenVertexArrays(1, &quad_vao);
		glGenBuffers(1, &quad_vbo);
		glBindVertexArray(quad_vao);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quad_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}