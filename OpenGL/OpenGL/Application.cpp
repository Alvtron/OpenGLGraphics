#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Level.h"
#include "VegardLevel.h"
#include "VetleLevel.h"
#include "ThomasLevel.h"
#include "TextExampleLevel.h"
#include <time.h>
//Levels

// Presets
#define DEBUG true
#define FULLSCREEN false
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
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

void initGLFWindow()
{

	if (DEBUG) {
		std::cout << "[DEBUG MODUS]" << std::endl;
		start_time_init = clock();
	}

	// Initialize GLFW
	int glfw = glfwInit();

	if (glfw == GLFW_FALSE)
	{
		std::cout << "Error: Failed to initialize GLFW" << std::endl;
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
		std::cout << "Error: Failed to create GLFW window" << std::endl;
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
		std::cout << "Error: " << glewGetErrorString(glew) << std::endl;
		return;
	}
	if (DEBUG) {
		std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
		std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Initialation time: " << getTimeSeconds(start_time_init, clock()) << " seconds" << std::endl;
	}
}


void main()
{

	//init GLFW window
	initGLFWindow();

	// Draw wireframe
	if (DRAW_WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//Vegard::VegardLevel vegardLevel;
	ThomasLevel thomasLevel;
	//vetle::VetleLevel vetleLevel;
	//TextExampleLevel textExampleLevel;

	try {
		
		//vegardLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		thomasLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		//vetleLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		//textExampleLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);

	}
	catch (int e) {
		std::cout << "Cannot init level Nr. " << e << std::endl;
		system("PAUSE");
		glfwTerminate();
		return;
	}

	try {
		while (!glfwWindowShouldClose(window)) {

			thomasLevel.loop();
			//vegardLevel.loop();
			//vetleLevel.loop();
			//textExampleLevel.loop();

		}
	}
	catch (int e)
	{
		std::cout << "Cannot loop level Nr. " << e << std::endl;
		system("PAUSE");
		glfwTerminate();
		return;
	}

	glfwTerminate();
}

// Calculate time passed between two timestamps and return it in seconds
double getTimeSeconds(clock_t time_begin, clock_t time_end) {
	return double(time_end - time_begin) / CLOCKS_PER_SEC;
}