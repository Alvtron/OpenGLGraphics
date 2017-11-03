#include "TextExampleLevel.h"

void processInputTextExampleLevel(GLFWwindow *window);

Text textExample;

void TextExampleLevel::init(GLFWwindow *window, int WINDOW_HEIGHT, int WINDOW_WIDTH)
{
	this->window = window;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	this->WINDOW_WIDTH = WINDOW_WIDTH;

	glClearColor(0.0f, 0.2f, 0.3f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, WINDOW_HEIGHT, WINDOW_WIDTH);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Init fonts and also select a font from fontfile in windows
	//This might take a while because this program need to calculate every letter in vector graphics
	textExample.initFonts("C:/Windows/Fonts/Arial.ttf", WINDOW_HEIGHT, WINDOW_WIDTH);


	// -------------------------------------------------------------------------------------------
	// How to get to shader in text class: (added default orthographic matrix if nothing is changed)
	// -------------------------------------------------------------------------------------------
	//text.textShader.use();
	//text.textShader.setMat4("Projection",projection)

}


void TextExampleLevel::loop()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Text, x, y, scale and color in vectorform
	textExample.RenderText("12345678", 0, 0, 1.0f, vec3(0.0f, 1.0f, 0.0f));
	textExample.RenderText("Dette er en text", 200.0f,100.0f, 1.0f, vec3(1.0, 0.0f, 0.2f));
	textExample.RenderText("WOHO!", 100.0f, 200.0f, 2.0f, vec3(0.0f, 0.5f, 0.5f));

	processInputTextExampleLevel(window);
	glfwSwapBuffers(window);
	glfwPollEvents();

}


void processInputTextExampleLevel(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
