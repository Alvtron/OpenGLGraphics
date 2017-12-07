#include "Rectangle.h"

Rect::Rect()
{
	createRectangle(WIDTH, HEIGHT, vec3(0.0f, 0.0f, 0.0f));
}

Rect::Rect(float width, float height)
{
	createRectangle(width, height, vec3(0.0f, 0.0f, 0.0f));
}

Rect::Rect(float width, float height, vec3 position)
{
	createRectangle(width, height, position);
}

Rect::~Rect()
{
}

void Rect::createRectangle(float width, float height, vec3 position) {
	float widthRadius = width / 2.0f;
	float heightRadius = height / 2.0f;

	indices = {
		0, 1, 2,
		2, 3, 0
	};

	vertices = {
		// Front
		vec3(-widthRadius, 0, -heightRadius),
		vec3(+widthRadius, 0, -heightRadius),
		vec3(+widthRadius, 0, +heightRadius),
		vec3(-widthRadius, 0, +heightRadius)
	};

	normals = {
		// Front
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	};

	uvs = {
		// Front
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f)
	};

	setColor();
	calculateTangents();
}