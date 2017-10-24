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
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

double getTimeSeconds(clock_t time_begin, clock_t time_end);
clock_t start_time_init;

//Enables Vsync
bool vsync = true;

// Window
const char window_title[] = "ITF21215 OpenGL group project";
const int openGL_min = 4, openGL_max = 4;
GLFWwindow* window;

/*


#==========================================================================================#

Meldig Fra Vegard (teksten kommer til å bli fjernet etterhvert)

Levelklassen! (ikke helt ferdig, men det funker for nå)

Den hovedsaklige planen var å lage en main level klasse, men fordi alle level klasser til å være
forskjellig, fant jeg det ut at det er enklere at vi lager nye klasser hver gang vi skal lage
en ny level.

men det må inneholde 2 metoder:

init() <--- her skal all kode kjøre før " while (!glfwWindowShouldClose(window)) " loopen kjører

tar imot parametere:
GLFWwindow *window,		int WINDOW_HEIGHT,		int WINDOW_WIDTH

Kan hjerne ta imot flere parametere med behov



loop() <-- her skal all kode kjøre som er inne i " while (!glfwWindowShouldClose(window))  " loopen kjøre

tar imot ingen parameter


Husk at det kun kan kjøres 1 level om gangen :) bare kommenter ut det levelklassen dere ikke bruker


#==========================================================================================#



*/

/*
	Melding fra Vetle: 
	For å bruke matteklassen, bare bruk #include "maths.h", da får dere med alt.
	Skal kommentere metodene etterhvert, forklare parametere og bruk etc.
	Har tenkt å lage en ny metode for å hente view matrisa uten bruk av glm.
*/

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
	if (DEBUG) std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

	//Enable vsync
	glfwSwapInterval(vsync);

	// Configure global OpenGL state
	glEnable(GL_DEPTH_TEST);

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
	
	//VegardLevel vegardLevel;
	//ThomasLevel thomasLevel;
	//VetleLevel vetleLevel;
	TextExampleLevel textExampleLevel;

	try {
		
		//vegardLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		//thomasLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		//vetleLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);
		textExampleLevel.init(window, WINDOW_HEIGHT, WINDOW_WIDTH);

	}
	catch (int e) {
		std::cout << "Cannot init level Nr. " << e << std::endl;
		system("PAUSE");
		glfwTerminate();
		return;
	}

	try {
		while (!glfwWindowShouldClose(window)) {

			//thomasLevel.loop();
			//vegardLevel.loop();
			//vetleLevel.loop();
			textExampleLevel.loop();

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