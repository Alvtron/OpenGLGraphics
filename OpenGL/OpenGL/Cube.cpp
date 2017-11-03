#include "Cube.h"

unsigned int Cube::num_cubes = 0; 

/* Create a Cube object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to add vertex data. */
Cube::Cube() : Mesh()
{
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_cubes++;
}

Cube::Cube(float width) : Mesh()
{
	vertices = createCube(width, width);
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_cubes++;
}

Cube::Cube(float width, float height) : Mesh()
{
	vertices = createCube(width, height);
	Mesh::createVertexData(vertices, normals, colors, textures, indices);
	num_cubes++;
}

/* De-constructor */
Cube::~Cube()
{
	num_cubes--;
}

/* Create a cube. Returns it's vertices */
std::vector<vec3> Cube::createCube(const float width, const float height) {
	float widthRadius = width / 2.0f;
	float heightRadius = height / 2.0f;
	return vertices = {
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
}

std::vector<vec3> Cube::getVertices()
{
	return vertices;
}

std::vector<vec3> Cube::getNormals()
{
	return normals;
}

std::vector<vec3> Cube::getColors()
{
	return colors;
}

std::vector<vec2> Cube::getTextures()
{
	return textures;
}

std::vector<unsigned int> Cube::getIndices()
{
	return indices;
}

/* Return number of cubes created on this stack */
int Cube::getNumCubes()
{
	return num_cubes;
}