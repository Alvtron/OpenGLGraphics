#include "Rectangle.h"
#include <cmath>

unsigned int Rect::num_rectangles = 0;

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect() : Mesh()
{
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_rectangles++;
}

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect(float width, float height) : Mesh()
{
	createRectangle(width, height, glm::vec3(0.0f, 0.0f, 0.0f));
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_rectangles++;
}

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect(float width, float height, glm::vec3 position) : Mesh()
{
	vertices = createRectangle(width, height, position);
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_rectangles++;
}

/* Deconstructor */
Rect::~Rect()
{
	num_rectangles--;
}

/* Create a rectangle. Returns it's vertices */
std::vector<glm::vec3> Rect::createRectangle(float width, float height, glm::vec3 position) {
	return {
		glm::vec3(-(width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		glm::vec3((width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		glm::vec3((width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z),
		glm::vec3(-(width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z)
	};
}

std::vector<glm::vec3> Rect::getVertices()
{
	return vertices;
}

std::vector<glm::vec3> Rect::getNormals()
{
	return normals;
}

std::vector<glm::vec3> Rect::getColors()
{
	return colors;
}

std::vector<glm::vec2> Rect::getTextures()
{
	return textures;
}

std::vector<unsigned int> Rect::getIndices()
{
	return indices;
}

/* Return width of rectangle */
float Rect::getWidth()
{
	return vertices[1].x - vertices[0].x;
}

/* Return height of rectangle */
float Rect::getHeight()
{
	return vertices[3].y - vertices[0].y;
}

/* Return area of rectangle */
float Rect::getArea()
{
	return getWidth() * getHeight();
}

/* Return number of rectangles created on this stack */
int Rect::getNumRectangles()
{
	return num_rectangles;
}
