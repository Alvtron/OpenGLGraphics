#include "Rectangle.h"

/* Create a Rectangle object that stores vertex data. */
Rect::Rect()
{
	createRectangle(WIDTH, HEIGHT, vec3(0.0f, 0.0f, 0.0f));
}

/* Create a Rectangle object that stores vertex data. */
Rect::Rect(float width, float height)
{
	createRectangle(width, height, vec3(0.0f, 0.0f, 0.0f));
}

/* Create a Rectangle object that stores vertex data. */
Rect::Rect(float width, float height, vec3 position)
{
	createRectangle(width, height, position);
}

/* De-constructor */
Rect::~Rect()
{
}

/* Create a rectangle. Returns it's vertices */
void Rect::createRectangle(float width, float height, vec3 position) {
	indices = {
		0, 1, 2,
		2, 3, 0
	};

	vertices = {
		vec3(-(width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		vec3((width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		vec3((width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z),
		vec3(-(width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z)
	};

	normals = {
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f)
	};

	uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f)
	};

	createColors();
	calculateTangents();
}