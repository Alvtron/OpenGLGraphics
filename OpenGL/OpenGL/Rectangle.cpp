#include "Rectangle.h"
#include <cmath>

unsigned int Rect::num_rectangles = 0;

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect() : Mesh()
{
	Mesh::createVertexData(vertices, NORMALS, colors, TEXTURES, INDICES);
	num_rectangles++;
}

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect(float width, float height) : Mesh()
{
	this->vertices[Ax] = -(width / 2.0f);
	this->vertices[Ay] = -(height / 2.0f);
	this->vertices[Bx] = (width / 2.0f);
	this->vertices[By] = -(height / 2.0f);
	this->vertices[Cx] = (width / 2.0f);
	this->vertices[Cy] = (height / 2.0f);
	this->vertices[Dx] = -(width / 2.0f);
	this->vertices[Dy] = (height / 2.0f);
	Mesh::createVertexData(vertices, NORMALS, colors, TEXTURES, INDICES);
	num_rectangles++;
}

/* Deconstructor */
Rect::~Rect()
{
	num_rectangles--;
}

/* [In progress] */
float Rect::getWidth()
{
	return 0;
}

/* [In progress] */
float Rect::getHeight()
{
	return 0;
}

/* [In progress] */
float Rect::getAreal()
{
	return 0;
}

/* Return number of rectangles created on this stack */
int Rect::getNumRectangles()
{
	return num_rectangles;
}
