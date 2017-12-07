#pragma once
#include "VetleLevel.h"
#include "Material.h"
#include "Shader.h"

namespace vetle {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);

	// Camera
	const vec3 SPAWN_POSITION(0.0f, 5.0f, 5.0f);
	Camera camera(SPAWN_POSITION);
	double lastX;
	double lastY;
	bool firstMouse = true;

	// Timing - time between current frame and last frame
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Global positions
	vec3 sunPosition(0.0f, -10.0f, 0.0f);
	vec3 groundPosition(0.0f, -10.0f, 0.0f);

	// Object colour
	vec3 sunColour(1.0f, 1.0f, 0.0f);

	// 3D Objects
	CubeMap cubemap = CubeMap();
	Rect ground = Rect(30.0f, 30.0f, groundPosition);
	Sphere sun = Sphere(2.0f, 3);
	float radius = 30.0f;
	float angle = 0.0f;

	// Textures
	Material sunTexture, groundTexture;

	// Shaders
	Shader cubeMapShader;
	Shader shader;

	void VetleLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
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
		// SHADER - Build and compile the shader program (with LearnOpenGL's provided shader class)
		// ===========================================================================================
		cubeMapShader.init("shaders/cubemap_vert.shader", "shaders/cubemap_frag.shader");
		shader.init("shaders/object_vert.shader", "shaders/obj_one_light_frag.shader");

		// ===========================================================================================
		// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
		// ===========================================================================================
		cubemap.storeOnGPU();
		ground.storeOnGPU();
		sun.storeOnGPU();

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

		sunTexture.addDiffuse(Texture("resources/textures/sun1.jpg"));
		sunTexture.addSpecular(Texture("resources/textures/1857-specexponent.jpg"));
		sunTexture.addNormal(Texture("resources/textures/1857-normal.jpg"));

		groundTexture.addDiffuse(Texture("resources/textures/10744-diffuse.jpg"));
		groundTexture.addSpecular(Texture("resources/textures/10744-specstrength.jpg"));
		groundTexture.addNormal(Texture("resources/textures/10744-normal.jpg"));
		groundTexture.addAmbientOcclusion(Texture("resources/textures/10744-ambientocclusion.jpg"));

	}

	void VetleLevel::loop()
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
		shader.setVec3("light.position", sunPosition);
		shader.setVec3("light.ambient", vec3(0.2f, 0.2f, 0.2f) + (vec3::scale(sunColour, 1.5f)));
		shader.setVec3("light.diffuse", vec3::scale(sunColour, 2.5f));
		shader.setVec3("light.specular", sunColour);
		shader.setFloat("light.constant", 1.0f);
		shader.setFloat("light.linear", 0.09f);
		shader.setFloat("light.quadratic", 0.032f);

		// Calculate View/Projection transformations
		mat4 projection = mat4::makePerspective(camera.Fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// -------------------------------------------------------------------------------------------
		// DRAW OBJECTS (see Rectangle/Cube class for draw functions)
		// -------------------------------------------------------------------------------------------
	
		ground.drawObject(&shader, groundPosition, 90.0f, vec3(1.0f, 0.0f, 0.0f), &groundTexture);
		sunPosition = vec3(radius * cos(angle * M_PI / 180.0f), radius * sin(angle * M_PI / 180.0f), 0.0f);
		sun.drawObject(&shader, sunPosition, &sunTexture);

		angle += 0.5f;
		
		// Draw cubemap (this must AFTER all other objects last or it will decrease peformance)
		cubemap.drawCubemap(&cubeMapShader, &camera, projection);

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

}