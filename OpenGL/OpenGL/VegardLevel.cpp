#pragma once 
#include "VegardLevel.h"
#include "Shader.h"

#if 0

namespace Vegard {
	//Prototyes
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window, float deltaTime);

	//Text
	Text text;
	bool playerConsole = true;

	// Camera
	Player player;
	float jumpStrength = 15.0f;

	vec3 SPAWN_POSITION(0.0f, 5.0f, 5.0f);
	//Camera camera(SPAWN_POSITION);
	double lastX;
	double lastY;
	bool firstMouse = true;
	bool flyingmode = false;
	// Timing - time between current frame and last frame
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Global positions
	vec3 sunPosition(0.0f, -10.0f, 0.0f);
	vec3 groundPosition(0.0f, -10.0f, 0.0f);

	// Object colour
	vec3 sunColour(1.0f, 1.0f, 1.0f);

	//Entity
	Entity gorundEnt(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0001f, 1.0f), vec3(100.0f, 100.0f, 100.0f), true);

	// 3D Objects
	Cube cube1 = Cube(boxEnt.scale.x);
	CubeMap cubemap = CubeMap();
	Diamond diamond = Diamond(1.0f);
	Rect ground = Rect();
	Sphere sun = Sphere(2.0f, 3);
	float radius = 20.0f;
	float angle = 90.0f;

	// Textures
	Material sunTexture, groundTexture, mixedstone, metal;

	// Shaders
	Shader cubeMapShader;
	Shader shader;

	

	void VegardLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Init fonts
		text.initFonts("C:/Windows/Fonts/Arial.ttf", WINDOW_HEIGHT, WINDOW_WIDTH);

		// ===========================================================================================
		// SHADER - Build and compile the shader program (with LearnOpenGL's provided shader class)
		// ===========================================================================================
		cubeMapShader.init("shaders/cubemap_vert.shader", "shaders/cubemap_frag.shader");
		shader.init("shaders/object_vert.shader", "shaders/obj_one_light_frag.shader");

		// ===========================================================================================
		// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
		// ===========================================================================================
		cube1.storeOnGPU();
		cubemap.storeOnGPU();
		diamond.storeOnGPU();
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

		mixedstone.addDiffuse(Texture("resources/textures/mixedstones-diffuse.jpg"));
		mixedstone.addSpecular(Texture("resources/textures/mixedstones-specular.jpg"));
		mixedstone.addNormal(Texture("resources/textures/mixedstones-normal.jpg"));
		mixedstone.addDisplacement(Texture("resources/textures/mixedstones-displace.jpg"));

		metal.addDiffuse(Texture("resources/textures/1857-diffuse.jpg"));
		metal.addSpecular(Texture("resources/textures/1857-specexponent.jpg"));
		metal.addNormal(Texture("resources/textures/1857-normal.jpg"));
		metal.addDisplacement(Texture("resources/textures/1857-displacement.jpg"));

		

		player.position = vec3(0.0f,13.0f,0.0f);
		player.hitbox = vec3(0.5f, 1.0f, 0.5f);
		player.camera.SetCameraPosition(player.position);
		player.addCollidableEntity(gorundEnt);
		player.addCollidableEntity(boxEnt);

	}

	void VegardLevel::loop()
	{
		// Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input (if any)
		processInput(window,deltaTime);


		// Background color (world color)
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		// Clear the depth buffer before each render iteration
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate shader when setting uniforms/drawing objects
		shader.use();
		shader.setFloat("material.shininess", 64.0f);
		shader.setVec3("viewPos", player.camera.Position);

		// light properties
		shader.setVec3("light.position", sunPosition);
		shader.setVec3("light.ambient", vec3(0.2f, 0.2f, 0.2f) + (vec3::scale(sunColour, 1.5f)));
		shader.setVec3("light.diffuse", vec3::scale(sunColour, 2.5f));
		shader.setVec3("light.specular", sunColour);
		shader.setFloat("light.constant", 1.0f);
		shader.setFloat("light.linear", 0.09f);
		shader.setFloat("light.quadratic", 0.032f);

		// Calculate View/Projection transformations
		mat4 projection = mat4::makePerspective(player.camera.Fov, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		mat4 view = player.camera.GetViewMatrix();

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// -------------------------------------------------------------------------------------------
		// DRAW OBJECTS (see Rectangle/Cube class for draw functions)
		// -------------------------------------------------------------------------------------------
		ground.drawObject(&shader, gorundEnt.position, gorundEnt.scale, 90.0f, vec3(1.0f, 0.0f, 0.0f), &groundTexture);
		//cube.drawObject(&shader, boxEnt.position, metal);
		diamond.drawObject(&shader, vec3(0.0f, 3.0f, 0.0f), vec3(2.0f, 2.0f, 2.0f), &mixedstone);
		cube1.drawObject(&shader, boxEnt.position, &metal);
		/*
		for (int i = -10; i < 10; i++)
			for (int j = -10; j < 10; j += 2) {
				cube.drawObject(&shader, vec3((float)i, 0.0f, (float)j), groundTexture);
				cube.drawObject(&shader, vec3((float)i, -0.25f, (float)j + 1.0f), metal);
			}
		*/
		sunPosition = vec3(radius * cos(angle * M_PI / 180.0f), radius * sin(angle * M_PI / 180.0f), 0.0f);
		sun.drawObject(&shader, sunPosition, &sunTexture);
		if (playerConsole) {
			text.RenderText(player.consolePlayerPosition(), 20.0f, 20.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(player.consolePlayerCollision(), 20.0f, 60.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(player.consoleOtherTings(), 20.0f, 100.0f, 0.4f, vec3(1.0f, 0.0f, 0.0f));
		}
		

		//Don't want the sun to rotate 
		//angle += 0.5f;

		// Draw cubemap (this must AFTER all other objects last or it will decrease peformance)
		cubemap.drawCubemap(&cubeMapShader, &player.camera, projection);

		// GLFW: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ===========================================================================================
	// PLAYER INPUTS
	// ===========================================================================================
	// Process all input: Query GLFW whether relevant keys are pressed/released this frame and react accordingly
	void processInput(GLFWwindow *window, float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		player.processInput(window, deltaTime, flyingmode);

	}
#if 0
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					player.camera.ProcessKeyboard(FORWARD, deltaTime, true, flyingmode);
				else
					player.camera.ProcessKeyboard(FORWARD, deltaTime, flyingmode);
			}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				player.camera.ProcessKeyboard(BACKWARD, deltaTime, true, flyingmode);
			else
				player.camera.ProcessKeyboard(BACKWARD, deltaTime, false, flyingmode);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				player.camera.ProcessKeyboard(LEFT, deltaTime, true, flyingmode);
			else
				player.camera.ProcessKeyboard(LEFT, deltaTime, false, flyingmode);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				player.camera.ProcessKeyboard(RIGHT, deltaTime, true, flyingmode);
			else
				player.camera.ProcessKeyboard(RIGHT, deltaTime, false, flyingmode);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			player.camera.ProcessKeyboardJump(deltaTime, jumpStrength);
		}
		else {
			//camera.ProcessKeyboardJump(deltaTime, -G);
		}

		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		{
			player.camera.ProcessKeyboardJump(deltaTime, -jumpStrength);
		}

#endif
	
	

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

		player.camera.ProcessMouseMovement(xoffset, yoffset);
	}

	// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		player.camera.setFOV((float)yoffset);
	}

}
#endif