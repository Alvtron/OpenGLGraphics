#include "Rectangle.h"

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures, tangents and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect() : Mesh()
{
	createRectangle(WIDTH, HEIGHT, vec3(0.0f, 0.0f, 0.0f));
}

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect(float width, float height) : Mesh()
{
	createRectangle(width, height, vec3(0.0f, 0.0f, 0.0f));
}

/* Create a Rectangle object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Rect::Rect(float width, float height, vec3 position) : Mesh()
{
	createRectangle(width, height, position);
}

/* Deconstructor */
Rect::~Rect()
{
}

/* Create a rectangle. Returns it's vertices */
void Rect::createRectangle(float width, float height, vec3 position) {
	vertex.indices = {
		0, 1, 2,
		2, 3, 0
	};

	vertex.vertices = {
		vec3(-(width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		vec3((width / 2.0f) + position.x, -(height / 2.0f) + position.y, 0.0f + position.z),
		vec3((width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z),
		vec3(-(width / 2.0f) + position.x, (height / 2.0f) + position.y, 0.0f + position.z)
	};

	vertex.normals = {
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f)
	};

	vertex.uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f)
	};

	MeshUtility::createColors(vertex);
	MeshUtility::calculateTangents(vertex);
}