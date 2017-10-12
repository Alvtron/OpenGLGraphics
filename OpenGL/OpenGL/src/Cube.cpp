/*

Created by Thomas Angeland, student at Østfold University College, Norway.

Refferences:

#1	Lectures, resources and examples by Lars Vidar Magnusson. Sourced 27.09.2017 from http://it.hiof.no/~larsvmag/itf21215_17/index.html.
Following his lectures and examples.

#2	LearnOpenGL articles by Joey de Vries. Sourced 27.09.2017 from https://learnopengl.com/.
My camera class is heavily based on Joey de Vries' camera class:
https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h (sourced 27.09.2017).
The shader class is created by Joey de Vries':
https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h (sourced 27.09.2017).
Joey de Vries code-examples on LearnOpenGL.com is licensed under
Creative Commons CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/legalcode)

#3	"Rooms and Mazes: A Procedural Dungeon Generator" by Bob Nystrom (21.12.2014).
Sourced 27.09.2017 from http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/.
My dungeon generator is written entirely by me, but based on Nystrom's guide.

#4	Hundreds of Stack Overflow articles. Thank God that webpage exists.

*/

#include "Cube.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> // OpenGL functions
#include <cmath>
#include "shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Cube::Cube() {}

Cube::~Cube()
{
}

float Cube::getWidth()
{
	return 0.0f;
}

float Cube::getHeight()
{
	return 0.0f;
}

float Cube::getVolume()
{
	return 0.0f;
}

void Cube::storeOnGPU()
{
	// Create VAO that stores the buffer objects. Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs.
	glGenVertexArrays(1, &VAO);
	// Create VBO that stores the vertex data
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the VAO before binding and configuring buffers
	glBindVertexArray(VAO);

	// Bind the VBO to the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy verticies into the VBO currently bound to the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Copy verticies into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals coordinate attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Cube::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular)
{
	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_diffuse);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_specular);

	// Bind VAO
	glBindVertexArray(VAO);

	// Calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, scale_vector);

	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular)
{
	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_diffuse);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_specular);

	// Bind VAO
	glBindVertexArray(VAO);

	// Calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation_degrees), rotation_vector);
	model = glm::scale(model, scale_vector);
	
	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::deAllocate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}