/*

Created by Thomas Angeland, student at Østfold University College, Norway.

*/

#include "Rectangle.h"
#include "shader.h"
#include <GLFW/glfw3.h> // OpenGL functions
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Rect::Rect()
{
	// A
	vertices[Ax] = -(WIDTH / 2.0f);
	vertices[Ay] = -(HEIGHT / 2.0f);
	vertices[Az] = 0.0f;
	vertices[Anx] = +0.0f;
	vertices[Any] = +0.0f;
	vertices[Anz] = -1.0f;
	vertices[Atx] = 0.0f;
	vertices[Aty] = 0.0f;
	// B
	vertices[Bx] = (WIDTH / 2.0f);
	vertices[By] = -(HEIGHT / 2.0f);
	vertices[Bz] = 0.0f;
	vertices[Bnx] = +0.0f;
	vertices[Bny] = +0.0f;
	vertices[Bnz] = -1.0f;
	vertices[Btx] = 1.0f;
	vertices[Bty] = 0.0f;
	// C
	vertices[Cx] = (WIDTH / 2.0f);
	vertices[Cy] = (HEIGHT / 2.0f);
	vertices[Cz] = 0.0f;
	vertices[Cnx] = +0.0f;
	vertices[Cny] = +0.0f;
	vertices[Cnz] = -1.0f;
	vertices[Ctx] = 1.0f;
	vertices[Cty] = 1.0f;
	// D
	vertices[Dx] = -(WIDTH / 2.0f);
	vertices[Dy] = (HEIGHT / 2.0f);
	vertices[Dz] = 0.0f;
	vertices[Dnx] = +0.0f;
	vertices[Dny] = +0.0f;
	vertices[Dnz] = -1.0f;
	vertices[Dtx] = 0.0f;
	vertices[Dty] = 1.0f;
}

Rect::Rect(float width, float height)
{
	// A
	vertices[Ax] = -(width / 2.0f);
	vertices[Ay] = -(height / 2.0f);
	vertices[Az] = 0.0f;
	vertices[Anx] = +0.0f;
	vertices[Any] = +0.0f;
	vertices[Anz] = -1.0f;
	vertices[Atx] = 0.0f;
	vertices[Aty] = 0.0f;
	// B
	vertices[Bx] = (width / 2.0f);
	vertices[By] = -(height / 2.0f);
	vertices[Bz] = 0.0f;
	vertices[Bnx] = +0.0f;
	vertices[Bny] = +0.0f;
	vertices[Bnz] = -1.0f;
	vertices[Btx] = 1.0f;
	vertices[Bty] = 0.0f;
	// C
	vertices[Cx] = (width / 2.0f);
	vertices[Cy] = (height / 2.0f);
	vertices[Cz] = 0.0f;
	vertices[Cnx] = +0.0f;
	vertices[Cny] = +0.0f;
	vertices[Cnz] = -1.0f;
	vertices[Ctx] = 1.0f;
	vertices[Cty] = 1.0f;
	// D
	vertices[Dx] = -(width / 2.0f);
	vertices[Dy] = (height / 2.0f);
	vertices[Dz] = 0.0f;
	vertices[Dnx] = +0.0f;
	vertices[Dny] = +0.0f;
	vertices[Dnz] = -1.0f;
	vertices[Dtx] = 0.0f;
	vertices[Dty] = 1.0f;
}

Rect::Rect(float x, float y, float z)
{
	// A
	vertices[Ax] = x - (WIDTH / 2.0f);
	vertices[Ay] = y - (HEIGHT / 2.0f);
	vertices[Az] = 0.0f;
	vertices[Anx] = +0.0f;
	vertices[Any] = +0.0f;
	vertices[Anz] = -1.0f;
	vertices[Atx] = 0.0f;
	vertices[Aty] = 0.0f;
	// B
	vertices[Bx] = x + (WIDTH / 2.0f);
	vertices[By] = y - (HEIGHT / 2.0f);
	vertices[Bz] = 0.0f;
	vertices[Bnx] = +0.0f;
	vertices[Bny] = +0.0f;
	vertices[Bnz] = -1.0f;
	vertices[Btx] = 1.0f;
	vertices[Bty] = 0.0f;
	// C
	vertices[Cx] = x + (WIDTH / 2.0f);
	vertices[Cy] = y + (HEIGHT / 2.0f);
	vertices[Cz] = 0.0f;
	vertices[Cnx] = +0.0f;
	vertices[Cny] = +0.0f;
	vertices[Cnz] = -1.0f;
	vertices[Ctx] = 1.0f;
	vertices[Cty] = 1.0f;
	// D
	vertices[Dx] = x - (WIDTH / 2.0f);
	vertices[Dy] = y + (HEIGHT / 2.0f);
	vertices[Dz] = 0.0f;
	vertices[Dnx] = +0.0f;
	vertices[Dny] = +0.0f;
	vertices[Dnz] = -1.0f;
	vertices[Dtx] = 0.0f;
	vertices[Dty] = 1.0f;
}

Rect::Rect(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz)
{
	// A
	vertices[Ax] = ax;
	vertices[Ay] = ay;
	vertices[Az] = az;
	vertices[Anx] = +0.0f;
	vertices[Any] = +0.0f;
	vertices[Anz] = -1.0f;
	vertices[Atx] = 0.0f;
	vertices[Aty] = 0.0f;
	// B
	vertices[Bx] = bx;
	vertices[By] = by;
	vertices[Bz] = bz;
	vertices[Bnx] = +0.0f;
	vertices[Bny] = +0.0f;
	vertices[Bnz] = -1.0f;
	vertices[Btx] = 1.0f;
	vertices[Bty] = 0.0f;
	// C
	vertices[Cx] = cx;
	vertices[Cy] = cy;
	vertices[Cz] = cz;
	vertices[Cnx] = +0.0f;
	vertices[Cny] = +0.0f;
	vertices[Cnz] = -1.0f;
	vertices[Ctx] = 1.0f;
	vertices[Cty] = 1.0f;
	// D
	vertices[Dx] = dx;
	vertices[Dy] = dy;
	vertices[Dz] = dz;
	vertices[Dnx] = +0.0f;
	vertices[Dny] = +0.0f;
	vertices[Dnz] = -1.0f;
	vertices[Dtx] = 0.0f;
	vertices[Dty] = 1.0f;
}


Rect::~Rect()
{
}

float Rect::getWidth()
{
	return vertices[Bx] - vertices[Ax];
}

float Rect::getHeight()
{
	return vertices[Dy] - vertices[Ay];
}

float Rect::getAreal()
{
	return getWidth() * getHeight();
}

void Rect::storeOnGPU()
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

void Rect::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular)
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rect::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular)
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rect::deAllocate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}