#include "Rectangle.h"
#include <cmath>

unsigned int Rect::num_rectangles = 0;

Rect::Rect() : Mesh()
{
	Mesh::createVertexData(vertices, NORMALS, colors, TEXTURES, INDICES);
	num_rectangles++;
}

Rect::Rect(float width, float height)
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

Rect::~Rect()
{
	num_rectangles--;
}

float Rect::getWidth()
{
	return 0;
}

float Rect::getHeight()
{
	return 0;
}

float Rect::getAreal()
{
	return 0;
}

int Rect::getNumRectangles()
{
	return num_rectangles;
}
