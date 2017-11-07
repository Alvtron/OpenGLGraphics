#include "Cube.h"

/* Create a Cube object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to add vertex data. */
Cube::Cube() : Mesh()
{
	createCube(WIDTH, HEIGHT);
}

Cube::Cube(float width) : Mesh()
{
	createCube(width, width);
}

Cube::Cube(float width, float height) : Mesh()
{
	createCube(width, height);
}

/* De-constructor */
Cube::~Cube()
{
}

/* Create a cube. Returns it's vertices */
void Cube::createCube(const float width, const float height) {
	float widthRadius = width / 2.0f;
	float heightRadius = height / 2.0f;

	vertex.indices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	vertex.vertices = {
		// Front
		vec3(-widthRadius, -heightRadius, -widthRadius),
		vec3(+widthRadius, -heightRadius, -widthRadius),
		vec3(+widthRadius, +heightRadius, -widthRadius),
		vec3(-widthRadius, +heightRadius, -widthRadius),
		// Back
		vec3(-widthRadius, -heightRadius, +widthRadius),
		vec3(+widthRadius, -heightRadius, +widthRadius),
		vec3(+widthRadius, +heightRadius, +widthRadius),
		vec3(-widthRadius, +heightRadius, +widthRadius),
		// Left
		vec3(-widthRadius, -heightRadius, +widthRadius),
		vec3(-widthRadius, -heightRadius, -widthRadius),
		vec3(-widthRadius, +heightRadius, -widthRadius),
		vec3(-widthRadius, +heightRadius, +widthRadius),
		// Right
		vec3(+widthRadius, -heightRadius, -widthRadius),
		vec3(+widthRadius, -heightRadius, +widthRadius),
		vec3(+widthRadius, +heightRadius, +widthRadius),
		vec3(+widthRadius, +heightRadius, -widthRadius),
		// Bottom
		vec3(-widthRadius, -heightRadius, -widthRadius),
		vec3(+widthRadius, -heightRadius, -widthRadius),
		vec3(+widthRadius, -heightRadius, +widthRadius),
		vec3(-widthRadius, -heightRadius, +widthRadius),
		// Top
		vec3(-widthRadius, +heightRadius, -widthRadius),
		vec3(+widthRadius, +heightRadius, -widthRadius),
		vec3(+widthRadius, +heightRadius, +widthRadius),
		vec3(-widthRadius, +heightRadius, +widthRadius)
	};

	vertex.normals = {
		// Front
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		// Back
		vec3(0.0f, 0.0f, +1.0f),
		vec3(0.0f, 0.0f, +1.0f),
		vec3(0.0f, 0.0f, +1.0f),
		vec3(0.0f, 0.0f, +1.0f),
		// Left
		vec3(-1.0f, 0.0f, 0.0f),
		vec3(-1.0f, 0.0f, 0.0f),
		vec3(-1.0f, 0.0f, 0.0f),
		vec3(-1.0f, 0.0f, 0.0f),
		// Right
		vec3(1.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		// Bottom
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f),
		// Top
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f)
	};

	vertex.uvs = {
		// Front
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Back
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Left
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Right
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Bottom
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f),
		// Top
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f)
	};
	MeshUtility::createColors(vertex);
	MeshUtility::calculateTangents(vertex);
}