#include "Rectangle.h"
#include <cmath>

unsigned int Rect::num_rectangles = 0;

Rect::Rect()
{
	Mesh::vertices = this->vertices;
	Mesh::normals = this->NORMALS;
	Mesh::colors = this->colors;
	Mesh::textures = this->TEXTURES;
	Mesh::indices = this->INDICES;
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
	Mesh::vertices = this->vertices;
	Mesh::normals = this->NORMALS;
	Mesh::colors = this->colors;
	Mesh::textures = this->TEXTURES;
	Mesh::indices = this->INDICES;
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
