#include <GL/glew.h>
#include <GLFW/glfw3.h>
// STB: Texture loader for several different types of image files
#include "stb_image.h"
// GLM: Matrix and vector math-library 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// Shaders and camera class, based on Joey de Vries' camera and shader class from learnOpenGL.com.
#include "shader.h"
#include "camera.h"
// Dungeon class created by Thomas Angeland for creating random-generated dungeons in adjustable sizes.
#include "Dungeon.h"
// 3D Object classes
#include "Rectangle.h"
#include "Cube.h"
// General C++ (and C++11) libraries
#include <iostream>
#include <string>
#include <vector>

// Presets
#define DEBUG true
#define FULLSCREEN true
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

const char window_title[] = "ITF21215 OpenGL group project";
const int openGL_min = 4, openGL_max = 4;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// Camera
Camera camera;
double lastX = WINDOW_WIDTH / 2.0f;
double lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// Global positions
glm::vec3 lightPosition = glm::vec3(0.0f, 5.0f, 0.0f);

// ===========================================================================================
// PROGRAM START
// ===========================================================================================

int main(void)
{
	// Creating a camera for player movement, set spawn position
	camera = Camera(glm::vec3(0.0f, 2.0f, 3.0f));

	glfwInit();
	// Set GLFW to use OpenGL version 4.5, both minor and major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_max);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_min);
	// Get access to a smaller subset of OpenGL features (no backwards-compatibility)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
		return -1;

	// Create a window and it's OpenGL context
	if (FULLSCREEN) window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title, glfwGetPrimaryMonitor(), NULL);
	else window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title, NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set actionlisteners for window resize, mouse and scrolling
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Tell GLFW to capture the players mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Configure global OpenGL state
	glEnable(GL_DEPTH_TEST);

	// Initialize GLEW and check if it's OK
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW ERROR" << std::endl;

	// ===========================================================================================
	// SHADER - Build and compile the shader program (with LearnOpenGL's provided shader class)
	// ===========================================================================================
	Shader shader("src/shaders/vertex_shader.vert", "src/shaders/fragment_shader.frag");
	Shader lightShader("src/shaders/light_shader.vert", "src/shaders/light_shader.frag");

	// ===========================================================================================
	// 3D OBJECTS - Set up vertex data and buffers and configure vertex attributes
	// ===========================================================================================

	Cube cube = Cube();
	cube.storeOnGPU();

	Rect plane = Rect();
	plane.storeOnGPU();

	// ===========================================================================================
	// LOAD TEXTURES
	// ===========================================================================================
	unsigned int tx_diff = loadTexture(std::string("src/resources/textures/1857-diffuse.jpg").c_str());
	unsigned int tx_spec = loadTexture(std::string("src/resources/textures/1857-specexponent.jpg").c_str());

	// Texture shading configuration
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

	// ===========================================================================================
	// RENDER LOOP
	// ===========================================================================================
	while (!glfwWindowShouldClose(window)) {

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
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocate all resources once they've outlived their purpose:
	plane.deAllocate();
	cube.deAllocate();

	// GLFW: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
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
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// GLFW: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.setFOV((float)yoffset);
}

// ===========================================================================================
// OTHER FUNCTIONS
// ===========================================================================================

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